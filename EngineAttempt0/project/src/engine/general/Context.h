#pragma once
#include "pch.h"

/*
* The context static class.
*/
class Context
{
	public:
	static bool CreateContext(int screenWidth, int screenHeight, std::string title);

	//Returns true if the window should close.
	inline static bool WindowShouldClose()
	{
		return glfwWindowShouldClose(mWindow);
	}

	//Returns current context's window.
	inline static GLFWwindow* GetMainWindow()
	{
		return mWindow;
	}

	//Returns the current window's dimensions.
	inline static vec2 GetCurrentDimensions()
	{
		return mScreenDimensions;
	}

	//Frees all Context resources.
	static void Terminate();

	//Swaps the window's color buffers.
	static void SwapBuffers();

	//GLFW window resize callback.
	static void resize_callback(GLFWwindow* window, int width, int height);

	/*
	* Request the user's attention by making the minimized application icon flash.
	*/
	static void RequestAttention();

	private:
	static GLFWwindow* mWindow;
	static bool mOK;
	static vec2 mScreenDimensions;
};
