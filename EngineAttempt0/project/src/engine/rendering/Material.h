#pragma once
#include "pch.h"
#include "Shader.h"

class Material
{
	public:
	bool cullBackFace = true;
	Material(ShaderProgram* shader,	std::string id)
	{
		mShader = shader;
		RegisterMaterial(id);
	}

	Material()
	{
	
	}

	inline ShaderProgram* GetShader()
	{
		return mShader;
	}

	void ChangeShader(ShaderProgram* otherShader)
	{
		mShader = otherShader;
	}

	void ApplyMaterial()
	{
		if (cullBackFace)
		{
			glEnable(GL_CULL_FACE);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		Apply();
	}

	void SubmitMVP(mat4 model, mat4 view, mat4 projection)
	{
		mShader->SetMat4f("model", model);
		mShader->SetMat4f("view", view);
		mShader->SetMat4f("projection", projection);
	}

	void Bind()
	{
		mShader->RunProgram();
	}

	static Material* GetMaterial(std::string matID)
	{
		std::unordered_map<std::string, Material*>::iterator it = matPool.find(matID);

		if (it != matPool.end())
		{
			return it->second;
		}
		
		return nullptr;
	}

	protected:

	virtual void Apply()
	{
		
	}

	ShaderProgram* mShader = 0;

	private:

	void RegisterMaterial(std::string matID)
	{
		matPool.insert(std::make_pair(matID, this));
	}

	static std::unordered_map<std::string, Material*> matPool;
};