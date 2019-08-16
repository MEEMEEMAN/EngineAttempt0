#pragma once
#include "pch.h"
#include "..//Input.h"
#include "Component.h"
#include "Time.h"

/*
* Camera class, acts as a freecam
*/
class Camera : public Component
{
	public:

	Camera(float fov, float screenWidth, float screenHeight)
	{
		mProjectionMatrix = glm::perspective(glm::radians(fov),
			screenWidth / screenHeight, 0.01f, 1000.0f);
	}

	void Update() override
	{
		vec2 mouseDelta = Input::GetMouseDelta() * 0.1f;
		mPitch += mouseDelta.y;
		mYaw += mouseDelta.x;

		if (mYaw < 0)
		{
			mYaw = fmod(mYaw, -360.0f);
		}
		else if (mYaw > 0)
		{
			mYaw = fmod(mYaw, 360.0f);
		}

		if (mPitch < 0)
		{
			mPitch = fmod(mPitch, -360.0f);
		}
		else if (mPitch > 0)
		{
			mPitch = fmod(mPitch, 360.0f);
		}

		mPitch = glm::clamp(mPitch, -90.0f, 90.0f);

		mViewMatrix = mat4(1);
		mViewMatrix = glm::rotate(mViewMatrix ,glm::radians(mPitch), vec3(1, 0, 0));
		mViewMatrix = glm::rotate(mViewMatrix ,glm::radians(mYaw), vec3(0, 1, 0));

		mat4 inverse = glm::inverse(mViewMatrix);
		vec3 front = glm::normalize(glm::vec3(inverse[2]));

		vec3 right = glm::normalize(glm::cross(front, vec3(0,1,0)));
		vec3 top = glm::normalize(glm::cross(front, right));

		bool invert = false;
		if (mPitch >= 90.0f || mPitch <= -90.0f)
		{
			invert = true;
		}

		if (invert)
		{
			right *= -1;
		}

		if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
		{
			timer += Time::DeltaTime();
		}
		else
		{
			timer = 1;
		}
		
		vec2 wasd = Input::GetWASDNormalized() * 3.0f * (float)Time::DeltaTime() * (timer * timer);
		position += front * wasd.y;
		position += right * wasd.x;

		mViewMatrix = glm::translate(mViewMatrix, position);
	}

	inline mat4 GetViewMatrix()
	{
		return mViewMatrix;
	}

	inline mat4 GetProjectionMatrix()
	{
		return mProjectionMatrix;
	}

	vec3 position = vec3(0);
	private:
	float timer = 1;
	float mPitch = 0, mYaw = 0;
	mat4 mViewMatrix = mat4(1), mProjectionMatrix = mat4(1);

};