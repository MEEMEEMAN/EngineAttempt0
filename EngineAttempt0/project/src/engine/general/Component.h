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

	inline void SetActive(bool value)
	{
		mActive = value;
	}

	inline bool isActive()
	{
		return mActive;
	}

	void Destroy();

	protected:
	virtual void Update()
	{

	}

	virtual void Start()
	{

	}
	bool mActive = true;
};