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

	MasterRenderer(Camera* renderCamera)
	{
		cam = renderCamera;
	}

	MasterRenderer()
	{

	}

	void SubmitRender(MeshRenderer* model, Material* mat)
	{
		AddToQueue(model, mat);
	}

	void InitiateRender()
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
					cam->GetViewMatrix(), cam->GetProjectionMatrix());

				threeDRenderer.Draw(&it->second[i]->rawmodel);
			}
		}

		renderQueue.clear();
	}

	void SetCam(Camera* camera)
	{
		cam = camera;
	}

	private:

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

	Camera* cam = 0;
	ThreeDRenderer threeDRenderer;
	std::map<Material*, std::vector<MeshRenderer*>> renderQueue;
};