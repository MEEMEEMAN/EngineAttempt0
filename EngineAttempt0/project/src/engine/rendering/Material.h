#pragma once
#include "pch.h"
#include "Shader.h"

class Material
{
	public:
	Material(ShaderProgram* shader,	std::string id)
	{
		CreateMaterial(shader, id);
	}

	Material()
	{
		
	}

	/*
	* Returns the material's shader.
	*/
	inline ShaderProgram* GetShader() const
	{
		return mShader.get();
	}

	/*
	* Swap the material's shader with a different one.
	*/
	void SwapShader(ShaderProgram* otherShader)
	{
		mShader.reset(otherShader);
	}

	/*
	* Submit the Model-View-Projection matrices to the material's shader.
	*/
	virtual void SubmitMVP(mat4 model, mat4 view, mat4 projection)
	{
		mShader->SetMat4f("model", model);
		mShader->SetMat4f("view", view);
		mShader->SetMat4f("projection", projection);
	}

	/*
	* Binds the material.
	* Initiates bind/unbind callback functions.
	*/
	void Bind()
	{
		if(currentMaterial == this)
			return;

		if(currentMaterial != nullptr)
			InitiateUnbindCallbacks();

		mShader->RunProgram();
		ApplyMaterial();

		currentMaterial = this;
		InitiateBindCallbacks();
	}

	/*
	* Returns a pointer to a material via the provided string material ID.
	*/
	static Material* const GetMaterial(std::string matID)
	{
		std::unordered_map<std::string, Material*>::iterator it = matPool.find(matID);

		if (it != matPool.end())
		{
			return it->second;
		}
		
		conlog("Material by the ID \"" << matID << "\" does not exist.");
		return nullptr;
	}

	/*
	* Returns all existing registered material id's.
	*/
	static std::vector<std::string> const GetMaterialIds()
	{
		return ids;
	}

	/*
	* Is backface culling activated while this material is bound?
	*/
	inline bool isCullFace() const
	{
		return cullBackFace;
	}

	/*
	* Should backface culling be allowed while this material is bound?
	*/
	inline void SetFaceCull(bool value)
	{
		cullBackFace = value;
	}

	/*
	* Static cleanup function.
	* Called typically at the end of the application's lifetime.
	* cleans up the registered material pool.
	*/
	static void CleanUp()
	{
		matPool.clear();
		ids.clear();
	}

	/*
	* Whenever the material gets bound by the renderer, the entered function will get invoked.
	*/
	void SubscribeBindCallback(void (*func)())
	{
		bindCallbacks.push_back(func);
	}

	/*
	* Whenever the material gets unBound by the renderer, the entered function will get invoked.
	*/
	void SubscribeUnBindCallback(void (*func)())
	{
		unbindCallbacks.push_back(func);
	}

	/*
	* Initiates the invoking of all of the material's subscribed functions.
	* should NOT be called by any non renderer related class. just pretend this function doe not exist.
	*/
	void InitiateUnbindCallbacks()
	{
		for (size_t i = 0; i < unbindCallbacks.size(); i++)
		{
			(*unbindCallbacks[i])();
		}
	}

	/*
	* Initiates the invoking of all of the material's subscribed functions.
	* should NOT be called by any non renderer related class. just pretend this function doe not exist.
	*/
	void InitiateBindCallbacks()
	{
		for (size_t i = 0; i < bindCallbacks.size(); i++)
		{	
			(*bindCallbacks[i])();
		}
	}

	protected:

	void CreateMaterial(ShaderProgram* shader, std::string id)
	{
		if (std::find(ids.begin(), ids.end(), id) != ids.end())
		{
			conlog("Material ID \"" << id << "\" already exists.");
			return;
		}

		mShader.reset(shader);
		ids.push_back(id);
		RegisterMaterial(id);
	}

	/*
	* A virtual function that provides an opportunity for any deriving materials to
	bind their things.
	*/
	virtual void ApplyOnBind()
	{
		
	}

	private:

	std::unique_ptr<ShaderProgram> mShader;
	bool cullBackFace = true;

	void RegisterMaterial(std::string matID)
	{
		matPool.insert(std::make_pair(matID, this));
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

		ApplyOnBind();
	}

	std::vector<void(*)()> bindCallbacks;
	std::vector<void(*)()> unbindCallbacks;
	static std::unordered_map<std::string, Material*> matPool;
	static std::vector<std::string> ids;
	static Material* currentMaterial;
};