#pragma once
#include "pch.h"
#include "Camera.h"
#include "GameObject.h"

class Scene
{
	public:

	Scene(Camera* cam)
	{
		
	}

	Scene()
	{

	}

	void UpdateRootGameObjects()
	{
		for (size_t i = 0; i < gameObjectRoots.size(); i++)
		{
			gameObjectRoots[i]->Update();
		}
	}

	void StartRootGameObjects()
	{
		for (size_t i = 0; i < gameObjectRoots.size(); i++)
		{
			gameObjectRoots[i]->StartComponents();
		}
	}

	void PreRenderUpdateRoots()
	{
		for (size_t i = 0; i < gameObjectRoots.size(); i++)
		{
			gameObjectRoots[i]->PreRender();
		}
	}

	void PostRenderUpdateRoots()
	{
		for (size_t i = 0; i < gameObjectRoots.size(); i++)
		{
			gameObjectRoots[i]->PostRender();
		}
	}
	
	Camera* GetMainCamera() const
	{
		return sceneCamera;
	}

	protected:
	Camera* sceneCamera = nullptr;

	virtual void ConstructScene()
	{
		
	}


	std::vector<GameObject*> gameObjectRoots;
};