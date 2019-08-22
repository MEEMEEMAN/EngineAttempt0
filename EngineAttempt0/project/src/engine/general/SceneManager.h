#pragma once
#include "pch.h"
#include "Scene.h"

class SceneManager
{
	public:

	static void SetSceneAsCurrent(Scene* scene)
	{
		currentScene = scene;
	}

	static void SceneUpdate()
	{
		currentScene->UpdateRootGameObjects();
	}

	static void PreRenderUpdate()
	{
		currentScene->PreRenderUpdateRoots();
	}

	static void PostRenderUpdate()
	{
		currentScene->PostRenderUpdateRoots();
	}

	static Scene* GetCurrentScene()
	{
		return currentScene;
	}

	private:
	static Scene* currentScene;
};