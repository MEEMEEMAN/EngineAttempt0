#pragma once
#include "Context.h"
GLFWwindow* Context::mWindow;
vec2 Context::mScreenDimensions;
bool Context::mOK;


bool Context::CreateContext(int screenWidth, int screenHeight, std::string title)
{
	if (!glfwInit())
	{
		conlog("[CONTEXT ERROR]failed to initialize glfw.");
		mOK = false;
		return mOK;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), 0, 0);
	mScreenDimensions.x = screenWidth;
	mScreenDimensions.y = screenHeight;
	glfwMakeContextCurrent(mWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		mOK = false;
		return mOK;
	}
	glViewport(0,0, screenWidth, screenHeight);
	glfwSetWindowSizeCallback(mWindow, resize_callback);
	

	mOK = true;
	
	std::stringstream ss;
	ss << "----- System info -----\n";
	ss << "Video Card: " << glGetString(GL_RENDERER) << "\n";
	ss << "Vendor: " << glGetString(GL_VENDOR) << "\n";
	ss << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
	ss << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
	ss << "-----------------------";
	conlog(ss.str());

	return mOK;
}

void Context::Terminate()
{
	glfwTerminate();
}

void Context::SwapBuffers()
{
	glfwSwapBuffers(mWindow);
}

void Context::resize_callback(GLFWwindow* window, int width, int height)
{
	mScreenDimensions.x = width;
	mScreenDimensions.y = height;
	glViewport(0, 0, width, height);
}