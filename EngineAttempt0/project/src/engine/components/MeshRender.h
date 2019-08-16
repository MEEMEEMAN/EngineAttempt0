#pragma once
#include "pch.h"
#include "..//general/Component.h"
#include "..//general/GameObject.h"
#include "..//rendering/RawModel.h"
#include "..//rendering/Loader.h"

class MasterRenderer;

class MeshRenderer : public Component
{
	public:
	static MasterRenderer* renderer;

	MeshRenderer() {};

	/*
	* RawModel gets loaded up from a specified filepath
	* the material initializes and creates a shader from the
		"project/src/engine/shaders/basic" vertex and fragment types.
	*/
	MeshRenderer(std::string meshFilepath)
	{	
		rawmodel = loader.ImportSimpleModel(meshFilepath);

		mat = Material(ShaderProgram("project/src/engine/shaders/basic.vert",
										"project/src/engine/shaders/basic.frag"));
	}

	void Update() override;

	Material mat;
	RawModel rawmodel;
	private:
	Loader loader;
};