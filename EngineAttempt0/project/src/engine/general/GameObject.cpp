#include "GameObject.h"

void GameObject::AddComponent(Component* component)
{
	component->owner = this;
	components.push_back(component);
}

void GameObject::Destroy()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Destroy();
		delete(components[i]);
	}
}

void GameObject::UpdateTransform()
{
	transform.UpdateTRS();
}

void GameObject::StartComponents()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->StartComponent();
	}
}

void GameObject::Update()
{
	UpdateTransform();

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->UpdateComponent();
	}
}

void GameObject::PreRender()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->PreRenderUpdate();
	}
}

void GameObject::PostRender()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->UpdatePostRender();
	}
}
