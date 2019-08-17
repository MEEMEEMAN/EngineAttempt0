#pragma once
#include "pch.h"
#include "Transform.h"

class GameObject;

class Component
{	

public:
GameObject* owner;
	
	void UpdateComponent();

	void StartComponent();

	void Destroy();

	protected:
	/*
	* The Update function gets invoked every frame.
	*/
	virtual void Update()
	{

	}

	/*
	* The Start function gets invoked on Component instantiation.
	* Start gets called after the constructor, only once the Component is added to the GameObject
	successfully.
	*/
	virtual void Start()
	{

	}
};