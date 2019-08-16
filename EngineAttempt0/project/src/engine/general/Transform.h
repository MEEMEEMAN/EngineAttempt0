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

	vec3 position = vec3(0), rotaiton = vec3(0), scale = vec3(1);
	mat4 modelMatrix = mat4(1);
	private:

};