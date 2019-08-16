#pragma once
#include "pch.h"
#include "RawModel.h"


class ThreeDRenderer
{
	public:
	/*
	* This function gets called whenever a model needs to be drawn. This function binds the respective RawWModel
	  and draws it via the parameters provided by the RawModel.
	*/
	void Draw(RawModel* model);

};