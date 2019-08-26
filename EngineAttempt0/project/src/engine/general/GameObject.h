#pragma once
#include "pch.h"
#include "Transform.h"
#include "Component.h"

/*
* The building block of all game related objects, wheter it is UI, a weapon, a player or anything
that can be represented as an object in space.
*/
class GameObject
{
public:
	void AddComponent(Component* component);

	template<typename T>
	T* GetComponent()
	{
		for (size_t i = 0; i < components.size(); i++)
		{
			if (T * derived = dynamic_cast<T*>(components[i].get()))
			{
				return derived;
			}
		}
		return 0;
	}

	/*
	* This function frees all of the memory that it occupies including the components.
	*/
	void Destroy();

	/*
	* This call first updates the Transform component, which applies the model matrix,
	after the Transform is updated, all corresponding components of this GameObject get updated
	aswell. the component update order is dependant on the order which they were added in.
	* Called pre render.
	*/
	void Update();

	/*
	* Called after the scene was rendererd.
	*/
	void PostRender();

	void PreRender();

	void SetActive(bool value)
	{
		mActive = value;
	}

	inline bool isActive() const
	{
		return mActive;
	}

	/*
	* Runs start method. 
	*/
	void StartComponents();

	void UpdateTransform();

	Transform transform;
protected:

	std::vector<std::unique_ptr<Component>> components;

	private:
	bool mActive = true;
};
