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

		ShaderProgram skyboxProgram("project/src/engine/shaders/skybox.vert", 
									"project/src/engine/shaders/skybox.frag");
		skyboxMat = Material(skyboxProgram);
		cubemapTexture = loader.LoadCubemap(cubefolderpath);
	}

	void Render()
	{
		glDepthMask(GL_FALSE);
		
		skyboxMat.Bind();

		mat4 view = cam->GetViewMatrix();
		view = mat4(mat3(view));

		static float timer = 0;
		timer += Time::DeltaTime();

		skyboxMat.GetShader()->SetMat4f("projection", cam->GetProjectionMatrix());
		skyboxMat.GetShader()->SetMat4f("view", view);
		skyboxMat.GetShader()->SetUniform1f("time", timer);
		cubemapTexture.BindCubemap(0);
		skyboxCube.Bind();
		glDrawElements(GL_TRIANGLES, skyboxCube.GetDrawCount(), GL_UNSIGNED_INT, 0);

		glDepthMask(GL_TRUE);
	}

	private:
	RawModel skyboxCube;
	Material skyboxMat;
	GLCube cubemapTexture;
};