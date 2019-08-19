#pragma once
#include "pch.h"
#include "..//rendering/GLTexture.h"
#include "..//rendering/Material.h"

class TexturedMaterial : public Material
{
	public:

	using Material::Material;

	/*
	* Add a texture to a shader without specifying a uniform variable. uniform name will default to
	the following format: textureN where N is the texture's index based on the order that you added the texture,
	and the total texture count. index starts from 0.
	*/
	void AddTexture(GLTexture texture)
	{
		mShader->RunProgram();

		textures.push_back(texture);
		
		std::stringstream ss;
		unsigned int value = textures.size() - 1;
		ss << "texture" << value;
		
		mShader->SetUniform1i(ss.str(),value);
	}

	/*
	* Add a texture and assign it to a shader uniform sampler2D variable.
	*/
	void AddTexture(GLTexture texture, std::string uniformName)
	{
		mShader->RunProgram();

		textures.push_back(texture);
		unsigned int value = textures.size() - 1;

		mShader->SetUniform1i(uniformName, value);
	}

	void ApplyShaderParameters() override
	{
		GLTexture::Unbind();
		for (size_t i = 0; i < textures.size(); i++)
		{
			textures[i].BindTexture2D(i);
		}
	}

	private:
	std::vector<GLTexture> textures;
};