#pragma once
#include "pch.h"
#include "..//general/Component.h"
#include "..//rendering/Loader.h"
#include "..//rendering/Material.h"
#include "..//rendering/GLCube.h"

class SkyboxRenderer
{
	public:
	Transform transform;
	Camera* cam = 0;

	SkyboxRenderer(std::string cubefolderpath)
	{
		Loader loader;
		skyboxCube = loader.ImportSimpleModel("project/assets/models/cube.glb");

		ShaderProgram* skyboxProgram = new ShaderProgram("project/assets/shaders/skybox.vert", 
									"project/assets/shaders/skybox.frag");
		skyboxMat = Material(skyboxProgram, "skyboxMat");
		skyboxMat.cullBackFace = false;
		cubemapTexture = loader.LoadCubemap(cubefolderpath);
	}

	float yaw = 0;
	void Rotate()
	{
		yaw += Time::DeltaTime() * 5;
	}

	void Render()
	{		
		skyboxMat.Bind();
		skyboxMat.ApplyMaterial();

		mat4 view = cam->GetViewMatrix();
		view = mat4(mat3(view));

		static float timer = 0;
		timer += Time::DeltaTime();
		mat4 model = mat4(1);
		model = glm::rotate(model, glm::radians(yaw), glm::vec3(1,1,1));

		skyboxMat.GetShader()->SetMat4f("model", model);
		skyboxMat.GetShader()->SetMat4f("projection", cam->GetProjectionMatrix());
		skyboxMat.GetShader()->SetMat4f("view", view);
		cubemapTexture.BindCubemap(0);
		skyboxCube.Bind();

		glDepthFunc(GL_LEQUAL);
		glDrawElements(GL_TRIANGLES, skyboxCube.GetDrawCount(), GL_UNSIGNED_INT, 0);
		glDepthFunc(GL_LESS);
	}

	private:
	RawModel skyboxCube;
	Material skyboxMat;
	GLCube cubemapTexture;
};