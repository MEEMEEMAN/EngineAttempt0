#pragma once
#include "pch.h"
#include "..//general/GameObject.h"
#include "..//rendering/Material.h"
#include "rendering/RawModel.h"
#include "systems/Renderable.h"
#include "general/Camera.h"

class RenderSystem
{
	public:

	static void Initialize(Camera* renderCamera)
	{
		mRenderCam = renderCamera;
	}

	static void SetRenderCam(Camera* camera)
	{
		mRenderCam = camera;
	}

	static void SubmitRender(Renderable renderable)
	{
		AddToPool(renderable);
	}

	static void QuickRender(Renderable renderable, Camera* renderCamera)
	{
		renderable.GetMaterial()->Bind();

		GameObject* renderedObject = renderable.owner;

		renderable.GetMaterial()->SubmitMVP(renderedObject->transform.GetModel(),
			renderCamera->GetViewMatrix(),
			renderCamera->GetProjectionMatrix());

		Draw(renderable.GetModel());
	}

	static void QuickRender(Renderable renderable)
	{
		renderable.GetMaterial()->Bind();

		GameObject* renderedObject = renderable.owner;

		renderable.GetMaterial()->SubmitMVP(renderedObject->transform.GetModel(),
			mRenderCam->GetViewMatrix(),
			mRenderCam->GetProjectionMatrix());

		Draw(renderable.GetModel());
	}

	static void BeginRender(Camera* renderCamera)
	{
		Render(renderCamera);
	}

	static bool BeginRender()
	{
		if(mRenderCam == nullptr)
			return false;

		Render(mRenderCam);
		return true;
	}

	static void ClearRenderBuffer()
	{
		renderBuffer.clear();
	}

	private:

	static void Render(Camera* renderCamera)
	{
		std::unordered_map<Material*, std::vector<Renderable>>::iterator it;
		it = renderBuffer.begin();

		for (; it != renderBuffer.end(); it++)
		{
			Material* currentMaterial = it->first;
			currentMaterial->Bind();

			for (size_t i = 0; i < it->second.size(); i++)
			{
				Renderable& renderable = it->second[i];
				GameObject* renderedObject = renderable.owner;

				currentMaterial->SubmitMVP(renderedObject->transform.GetModel(),
											renderCamera->GetViewMatrix(), 
											renderCamera->GetProjectionMatrix());
				Draw(renderable.GetModel());
			}
		}
	}

	static void Draw(RawModel model)
	{
		model.Bind();

		if (model.HasIndices())
		{
			glDrawElements(GL_TRIANGLES, model.GetDrawCount(), GL_UNSIGNED_INT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0,model.GetDrawCount());
		}
	}

	static void AddToPool(Renderable renderable)
	{
		std::unordered_map<Material*, std::vector<Renderable>>::iterator it;
		it = renderBuffer.find(renderable.GetMaterial());

		if (it != renderBuffer.end())
		{
			renderBuffer[renderable.GetMaterial()].push_back(renderable);
		}
		else
		{
			std::vector<Renderable> pool;
			pool.push_back(renderable);
			renderBuffer.insert(std::make_pair(renderable.GetMaterial(), pool));
		}
	}

	static Camera* mRenderCam;
	static std::unordered_map<Material*, std::vector<Renderable>> renderBuffer;
};