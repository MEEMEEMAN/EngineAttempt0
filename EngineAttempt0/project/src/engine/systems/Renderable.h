#pragma once
#include "pch.h"
#include "general/Component.h"
#include "..//rendering/Material.h"
#include "..//rendering/RawModel.h"

/*
* A base Renderable class that provides functionally for all things renderable.
*/
class Renderable : public Component
{
	public:

	Renderable()
	{
		
	}

	Material* GetMaterial() const
	{
		return mMaterial.get();
	}

	RawModel GetModel() const
	{
		return mModel;
	}

	void SetMaterial(Material* mat)
	{
		mMaterial.reset(mat);
	}

	void SetModel(RawModel model)
	{
		mModel = model;
	}

	protected:
	std::unique_ptr<Material> mMaterial;
	RawModel mModel;
};