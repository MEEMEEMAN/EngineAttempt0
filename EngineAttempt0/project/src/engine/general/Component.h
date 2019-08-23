#pragma once
#include "pch.h"
#include "Transform.h"


class GameObject;

class Component
{	

public:
GameObject* owner;
	
	void UpdateComponent();

	void UpdatePostRender();

	void PreRenderUpdate();

	void StartComponent();

	void Destroy();

	/*
	* Provides a way of dynamically instantiating classes.
	*/
	virtual auto clone() const -> Component*
	{
		return new Component(*this);
	}


	virtual std::string GetID() const
	{
		return "null";
	}

	protected:

	/*
	* The Update function gets invoked every frame.
	*/
	virtual void Update()
	{

	}

	/*
	* Gets called after rendering is finished.
	* Gets called every frame.
	*/
	virtual void PostRender()
	{

	}

	virtual void PreRender()
	{

	}

	/*
	* Gets called before the begginning of the first frame.
	* Gets called only once.
	*/
	virtual void Start()
	{

	}

	/*
	* Function is called whenever its time to destroy the gameobject. as a consequence,
	all of it's components get destroyed. components might have allocated memory so here they can free
	that memory.
	*/
	virtual void OnDestroy()
	{

	}
};