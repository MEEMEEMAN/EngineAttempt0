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
	* a RawModel gets loaded up from a specified filepath.
	* The inputed material will be used for rendering the RawModel.
	*/
	MeshRenderer(std::string meshFilepath, Material *material)
	{	
		rawmodel = loader.ImportSimpleModel(meshFilepath);
		mat = material;
	}

	auto clone() const -> MeshRenderer* override
	{
		return new MeshRenderer(*this);
	}

	virtual std::string GetID() const
	{
		return "MeshRenderer";
	}

	void Update() override;

	Material* mat = 0;
	RawModel rawmodel;
	private:
	Loader loader;
};