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

	void UpdateRootGameObjects()
	{
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i].Update();
		}
	}

	std::vector<GameObject> gameObjects;
};