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
		delete(components[i]);
	}
}

void GameObject::UpdateTransform()
{
	transform.UpdateTRS();
	/*
	mat4 modelMatrix = mat4(1);

	modelMatrix = glm::translate(modelMatrix, transform.position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotaiton.x), vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotaiton.y), vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotaiton.z), vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, transform.scale);

	transform.modelMatrix = modelMatrix;
	*/
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
