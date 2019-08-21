#pragma once
#include "pch.h"
#include "..//Input.h"
#include "Component.h"
#include "Time.h"
#include "GameObject.h"

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

	void Update() override;

	inline mat4 GetViewMatrix()
	{
		return mViewMatrix;
	}

	inline mat4 GetProjectionMatrix()
	{
		return mProjectionMatrix;
	}

	inline vec3 GetForwad()
	{
		return forwardVec;
	}

	inline vec3 GetUp()
	{
		return upVec;
	}

	void CollectInput();
	void CalcMatrix();

	private:
	float sprintTimer = 1;
	mat4 mViewMatrix = mat4(1), mProjectionMatrix = mat4(1);
	vec3 forwardVec, upVec;
};