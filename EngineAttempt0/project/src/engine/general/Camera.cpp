#pragma once
#include "Camera.h"

void Camera::CollectInput()
{
	vec2 mouseDelta = Input::GetMouseDelta() * 0.1f;
	owner->transform.rotaiton.x += mouseDelta.y;
	owner->transform.rotaiton.y += mouseDelta.x;

	if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
	{
		sprintTimer += Time::DeltaTime();
	}
	else
	{
		sprintTimer = 1;
	}

}

void Camera::CalcMatrix()
{
	if (owner->transform.rotaiton.y < 0)
	{
		owner->transform.rotaiton.y = fmod(owner->transform.rotaiton.y, -360.0f);
	}
	else if (owner->transform.rotaiton.y > 0)
	{
		owner->transform.rotaiton.y = fmod(owner->transform.rotaiton.y, 360.0f);
	}

	if (owner->transform.rotaiton.x < 0)
	{
		owner->transform.rotaiton.x = fmod(owner->transform.rotaiton.x, -360.0f);
	}
	else if (owner->transform.rotaiton.x > 0)
	{
		owner->transform.rotaiton.x = fmod(owner->transform.rotaiton.x, 360.0f);
	}

	owner->transform.rotaiton.x = glm::clamp(owner->transform.rotaiton.x, -90.0f, 90.0f);

	mViewMatrix = mat4(1);
	mViewMatrix = glm::rotate(mViewMatrix, glm::radians(owner->transform.rotaiton.x), vec3(1, 0, 0));
	mViewMatrix = glm::rotate(mViewMatrix, glm::radians(owner->transform.rotaiton.y), vec3(0, 1, 0));

	mat4 inverse = glm::inverse(mViewMatrix);
	vec3 front = glm::normalize(glm::vec3(inverse[2]));
	forwardVec = front;

	vec3 right = glm::normalize(glm::cross(front, vec3(0, 1, 0)));
	vec3 top = glm::normalize(glm::cross(front, right));
	upVec = top;

	bool invert = false;
	if (owner->transform.rotaiton.x >= 90.0f || owner->transform.rotaiton.x <= -90.0f)
	{
		invert = true;
	}

	if (invert)
	{
		right *= -1;
	}

	vec2 wasd = Input::GetWASDNormalized() * 3.0f * (float)Time::DeltaTime() * (sprintTimer * sprintTimer);
	owner->transform.position += front * wasd.y;
	owner->transform.position += right * wasd.x;

	mViewMatrix = glm::translate(mViewMatrix, owner->transform.position);
}

void Camera::Update()
{
	CollectInput();
	CalcMatrix();
}