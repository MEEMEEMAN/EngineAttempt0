#pragma once
#include "pch.h"
#include "general/Component.h"
#include "..//rendering/Material.h"
#include "..//rendering/RawModel.h"

class Renderable : public Component
{
	public:

	Renderable()
	{
		
	}

	Material* GetMaterial() const
	{
		return mMaterial;
	}

	RawModel GetModel() const
	{
		return mModel;
	}

	void SetMaterial(Material* mat)
	{
		mMaterial = mat;
	}

	void SetModel(RawModel model)
	{
		mModel = model;
	}

	protected:
	Material* mMaterial = nullptr;
	RawModel mModel;
};