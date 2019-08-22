#pragma once
#include "pch.h"
#include "Shader.h"
#include "RawModel.h"
#include "..//general/Camera.h"
#include "Renderer.h"
#include "Material.h"
#include "..//components/MeshRender.h"

class MasterRenderer
{
	public:

	static void Cleanup()
	{
		delete(instance);
	}

	MasterRenderer()
	{
	
	}

	void SetInstance(MasterRenderer* renderer)
	{
		instance = renderer;
	}

	void QuickRender(MeshRenderer* model, Material* mat, Camera* renderCam)
	{
		mat->Bind();
		mat->ApplyMaterial();

		GameObject* owner = model->owner;
		mat->SubmitMVP(owner->transform.GetModel(), renderCam->GetViewMatrix(), renderCam->GetProjectionMatrix());


	}

	void SubmitRender(MeshRenderer* model, Material* mat)
	{
		AddToQueue(model, mat);
	}

	static void BeginRender(Camera* renderCam)
	{
		instance->InitiateRender(renderCam);
	}

	void InitiateRender(Camera* renderCam)
	{
		std::map<Material*, std::vector<MeshRenderer*>>::iterator it;
		it = renderQueue.begin();
		for (; it != renderQueue.end() ;it++)
		{
			it->first->Bind();
			it->first->ApplyMaterial();
			//ShaderProgram* shader = it->first->GetShader();

			for (size_t i = 0; i < it->second.size(); i++)
			{
				GameObject *gamobject = it->second[i]->owner;
				it->first->
				SubmitMVP(gamobject->transform.GetModel(), 
					renderCam->GetViewMatrix(), renderCam->GetProjectionMatrix());

				threeDRenderer.Draw(&it->second[i]->rawmodel);
			}
		}
	}
	
	void Clear()
	{
		renderQueue.clear();
	}

	static void ClearQueue()
	{
		instance->Clear();
	}

	static MasterRenderer* Instance()
	{
		return instance;
	}

	private:
	static MasterRenderer* instance;

	void AddToQueue(MeshRenderer* rawmodel, Material* material)
	{
		std::map<Material*, std::vector<MeshRenderer*>>::iterator it;
		it = renderQueue.find(material);

		if (it != renderQueue.end())
		{
			it->second.push_back(rawmodel);
		}
		else
		{
			std::vector<MeshRenderer*> modelBuffer;
			modelBuffer.push_back(rawmodel);
			renderQueue.insert(std::make_pair(material, modelBuffer));
		}
	}

	ThreeDRenderer threeDRenderer;
	std::map<Material*, std::vector<MeshRenderer*>> renderQueue;
};