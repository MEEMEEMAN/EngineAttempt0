#pragma once
#include "pch.h"

class IMGUI
{
	public:

	//Initializes IMGUI
	static void Initialize(std::string GLSL_VERSION);

	//Runs all start of frame IMGUI code.
	static void BeginFrame();

	//Runs all end of frame IMGUI code.
	static void EndFrame();

	private:
};