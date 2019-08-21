#pragma once
#include "pch.h"

/*
* The class that represents the 3D position, rotaiton and scale.
*/
class Transform
{
public:
	Transform()
	{

	}

	/*
	* Apply the position,rotation,scale variables and store it as modelMatrix variable.
	* As the name suggets, the application order is Translate->Rotate->Scale.
	*/
	void UpdateTRS();

	/*
	* Apply the scale,rotation,position variables and store it as modelMatrix variable.
	* As the name suggets, the application order is Scale->Rotate->Translate.
	*/
	void UpdateSRT();

	/*
	* Returns the last calculated ModelMatrix.
	* ModelMatrix calculations occur when calling the UpdateTRS/UpdateSRT functions.
	*/
	inline mat4 GetModel() const
	{
		return mModelMatrix;
	}

	/*
	* Returns a forward vector relative to the Transform.
	*/
	inline vec3 GetForward() const
	{
		return mForward;
	}

	/*
	* Returns an upwards vector relative to the Transform.
	*/
	inline vec3 GetUp() const
	{
		return mUp;
	}

	/*
	* Returns the rightwards vector relative to the Transform.
	*/
	inline vec3 GetRight() const
	{
		return mRight;
	}

	vec3 position = vec3(0), rotaiton = vec3(0), scale = vec3(1);
	private:
		/*
		* Calculate the right, up and forward vector.
		*/
		void CalcDirections();

		mat4 mModelMatrix = mat4(1);
		vec3 mRight = vec3(0), mUp = vec3(0), mForward = vec3(0);
};