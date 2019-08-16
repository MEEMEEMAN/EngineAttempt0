#include "GameObject.h"

void GameObject::AddComponent(Component* component)
{
	component->owner = this;
	components.push_back(component);
	component->StartComponent();
}

void GameObject::Update()
{
	mat4 modelMatrix = mat4(1);

	modelMatrix = glm::translate(modelMatrix, transform.position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotaiton.x), vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotaiton.y), vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(transform.rotaiton.z), vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, transform.scale);

	transform.modelMatrix = modelMatrix;

	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->UpdateComponent();
	}
}
