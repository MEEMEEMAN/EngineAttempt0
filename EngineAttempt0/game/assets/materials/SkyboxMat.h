#pragma once
#include "engine.h"

class SkyboxMat : public Material
{
	public:

	using Material::Material;

	void SetCubemapTexture(GLCubeMap cubemap)
	{
		this->cubemap = cubemap;
	}

	void SubmitMVP(mat4 model, mat4 view, mat4 projection) override
	{
		mShader->SetMat4f("model", model);
		view = mat4(mat3(view));
		mShader->SetMat4f("view", view);
		mShader->SetMat4f("projection", projection);
	}

	void Apply() override
	{
		cubemap.BindCubemap(0);
	}

	GLCubeMap cubemap;
};