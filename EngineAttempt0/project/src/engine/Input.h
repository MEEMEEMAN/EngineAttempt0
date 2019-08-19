#pragma once
#include "pch.h"
#include "general/Context.h"

class Input
{
	static double MouseX, MouseY;
	static std::vector<int> m_heldKeyCache;
	static std::vector<int> m_MouseCache;
	static glm::vec2 m_MouseDelta;
	static float scrollDelta;
	static bool mFocused;
	
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		scrollDelta = yoffset;
	}
	
	static void focus_callback(GLFWwindow* window, int focused)
	{
		mFocused = focused;
	}

public:
	/*
	* Returns whether the requested key was pressed in the current frame or not.
	*/
	static bool GetKeyDown(int glkeycode);

	/*
	* Returns whether the requested key is being held or not.
	*/
	static bool GetKey(int glkeycode);

	/*
	* Returns a vec2 that states the extent of the mouse movement horizontally and vertically.
	*/
	static glm::vec2 GetMouseDelta();

	/*
	* This function determines if held keys/mouse buttons are still held, or were they released.
	* This function also calls glfwPollEvents().
	*/
	static void Update();

	/*
	* Returns whether the requested mouse button was pressed in the current frame or not.
	* Mouse button indices are as follows:
	  0 = left mouse button
	  1 = right mouse button
	  2 = middle mouse button(pressed scroll button)
	  indices are not limited to these values.
	*/
	static bool GetMouseDown(int mouseKey);

	/*
	* Returns whether the requested mouse button is being held or not.
	* Mouse button indices are as follows:
	  0 = left mouse button
	  1 = right mouse button	
	  2 = middle mouse button(pressed scroll button)
	  indices are not limited to these values.
	*/
	static bool GetMouse(int mouseKey);
	
	/*
	* Returns a mouse position that can exceed the window's borders, good for camera movement
	when LockCursor is active.
	*/
	static glm::vec2 GetMousePosition();

	/*
	* Returns a vector corresponding to the WASD or Arrow key inputs, 
	useful for implementing movement.
	* This function returns a NORMALIZED vector.
	*/
	static glm::vec2 GetWASDNormalized();

	/*
	* Returns a vector corresponding to the WASD or Arrow key inputs, 
	useful for implementing movement.
	* This function returns a NON-NORMALIZED vector.
	*/
	static glm::vec2 GetWASDVector();

	/*
	* Locking the cursor means to clamp the cursor to the middle of the screen and
	hide it.
	*/
	static void LockCursor(bool state);

	/*
	* Gets the mouse position in relation to the actual window's borders.
	* If the mouse gets out of the window, the reported position will only go as low as 0
	and as high as the current window's viewport dimension allows it to.
	*/
	static vec2 GetClampedMousePos();

	static void Initialize()
	{
		glfwSetScrollCallback(Context::GetMainWindow(), scroll_callback);
		glfwSetWindowFocusCallback(Context::GetMainWindow(), focus_callback);
	}

	inline static float GetScrollDelta()
	{
		return scrollDelta;
	}

	static inline vec2 GetScreenDimensions()
	{
		return Context::GetCurrentDimensions();
	}
};
