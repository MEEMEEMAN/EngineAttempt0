#include "Transform.h"

void Transform::UpdateTRS()
{
	mat4 modelMatrix = mat4(1);

	modelMatrix = glm::translate(modelMatrix, position);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.x), vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.y), vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.z), vec3(0, 0, 1));

	modelMatrix = glm::scale(modelMatrix, scale);
	mModelMatrix = modelMatrix;

	CalcDirections();
}

void Transform::UpdateSRT()
{
	mat4 modelMatrix = mat4(1);

	modelMatrix = glm::scale(modelMatrix, scale);

	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.x), vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.y), vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(rotaiton.z), vec3(0, 0, 1));

	modelMatrix = glm::translate(modelMatrix, position);

	mModelMatrix = modelMatrix;

	CalcDirections();
}

void Transform::CalcDirections()
{
	mat4 inverse = glm::inverse(mModelMatrix);
	mForward = glm::normalize(glm::vec3(inverse[2]));

	vec3 right = glm::normalize(glm::cross(mForward, vec3(0, 1, 0)));
	mRight = right;
	vec3 top = glm::normalize(glm::cross(mForward, mRight));
	mUp = top;
}
