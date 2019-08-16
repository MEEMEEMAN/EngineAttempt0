#include "Transform.h"

void Transform::UpdateTRS()
{
	modelMatrix = mat4(1);

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.x), vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.y), vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.z), vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, scale);

	modelMatrix = modelMatrix;
}