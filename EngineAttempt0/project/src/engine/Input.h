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
	static bool GetKeyDown(int glkeycode);
	static bool GetKey(int glkeycode);
	static glm::vec2 GetMouseDelta();
	//Also calls glfwPollEvents()
	static void Update();
	static bool GetMouseDown(int mouseKey);
	static bool GetMouse(int mouseKey);
	static glm::vec2 GetMousePosition();
	static glm::vec2 GetWASDNormalized();
	inline static float GetScrollDelta()
	{
		return scrollDelta;
	}
	//returns a not normalized WASD or arrow key press vector.
	static glm::vec2 GetWASDVector();
	static void LockCursor(bool state);

	static void Initialize()
	{
		glfwSetScrollCallback(Context::GetMainWindow(), scroll_callback);
		glfwSetWindowFocusCallback(Context::GetMainWindow(), focus_callback);
	}

	static inline vec2 GetClampedMousePos()
	{
		vec2 dimensions = Context::GetCurrentDimensions();
		vec2 ret = vec2(0);
		if (MouseX > dimensions.x)
		{
			ret.x = dimensions.x;
		}
		else if (MouseX < 0)
		{
			ret.x = 0;
		}
		else
		{
			ret.x = MouseX;
		}

		if (MouseY > dimensions.y)
		{
			ret.y = dimensions.y;
		}
		else if (MouseY < 0)
		{
			ret.y = 0;
		}
		else
		{
			ret.y = MouseY;
		}

		return ret;
	}
};
