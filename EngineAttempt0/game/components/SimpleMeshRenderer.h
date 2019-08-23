#pragma once
#include "engine.h"

class SimpleMeshRenderer : public Renderable
{
	public:

	std::string modelFilepath = "game/assets/models/cube.glb";

	void Start() override
	{
		Loader loader;
		SetModel(loader.ImportSimpleModel(modelFilepath));

		ShaderProgram* basic = new ShaderProgram("game/assets/shaders/basic.vert",
			"game/assets/shaders/basic.frag");

		TexturedMaterial* mat = new TexturedMaterial(basic, "basic");
		mat->AddTexture(loader.loadTexture("game/assets/textures/box.jpg", true), "image");
		SetMaterial(mat);
	}

	void Update() override
	{
		RenderSystem::SubmitRender(*this);
	}
};