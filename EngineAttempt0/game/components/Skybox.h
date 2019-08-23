#pragma once
#include "engine.h"
#include "..//assets/materials/SkyboxMat.h"

class Skybox : public Renderable
{
	public:

	void Start() override
	{
		Loader loader;
		SetModel(loader.ImportSimpleModel("game/assets/models/cube.glb"));

		ShaderProgram* skyboxShader = new ShaderProgram("game/assets/shaders/skybox.vert",
														"game/assets/shaders/skybox.frag");

		SkyboxMat* skyboxMat = new SkyboxMat(skyboxShader, "skyboxMat");
		skyboxMat->SetCubemapTexture(loader.LoadCubemap("game/assets/textures/spaceCubemap"));
		skyboxMat->cullBackFace = false;

		SetMaterial(skyboxMat);
	}

	void PreRender() override
	{
		glDepthFunc(GL_LEQUAL);
		RenderSystem::SubmitRender(*this);
	}

	void PostRender() override
	{
		glDepthFunc(GL_LEQUAL);
	}

	private:
};