#include "GameObject.h"

void GameObject::AddComponent(Component* component)
{
	component->owner = this;
	std::unique_ptr<Component> uniqComponent(component);
	components.push_back(std::move(uniqComponent));
}

void GameObject::Destroy()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->Destroy();
		components[i].reset();
	}
}

void GameObject::UpdateTransform()
{
	transform.UpdateTRS();
}

void GameObject::StartComponents()
{
	if (!mActive)
		return;

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->StartComponent();
	}
}

void GameObject::Update()
{
	if(!mActive)
		return;

	UpdateTransform();

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->UpdateComponent();
	}
}

void GameObject::PreRender()
{
	if (!mActive)
		return;

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->PreRenderUpdate();
	}
}

void GameObject::PostRender()
{
	if (!mActive)
		return;

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->UpdatePostRender();
	}
}
