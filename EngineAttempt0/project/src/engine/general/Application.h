#pragma once
#include "pch.h"
#include "Context.h"
#include "..//Input.h"

/*
* All data that corresponds to the application is stored here and can be
manipulated from here.
*/
class Application
{
	
	public:

	bool Initialize(float scrWidth, float scrHeight, std::string title)
	{
		mInitialized = Context::CreateContext(scrWidth, scrHeight, title);

		if (!mInitialized)
		{
			conlog("Failed to create a context.");
			return false;
		}

		Input::Initialize();
		return true;
	}

	private:
	bool mInitialized = false;
};