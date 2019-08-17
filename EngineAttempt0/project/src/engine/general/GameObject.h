#pragma once
#include "pch.h"
#include "Transform.h"
#include "Component.h"

/*
* The building block of all game related objects, wheter it is UI, a weapon, a player or anything
  related to the game aspect.
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
			if (T * derived = dynamic_cast<T*>(components[i]))
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
	*/
	void Update();

	Transform transform;
protected:

	std::vector<Component*> components;
};
