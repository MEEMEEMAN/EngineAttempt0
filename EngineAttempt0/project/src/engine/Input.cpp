#include "Input.h"

std::vector<int> Input::m_heldKeyCache;
std::vector<int> Input::m_MouseCache;
double Input::MouseX = 0.0f, Input::MouseY = 0.0f;
glm::vec2 Input::m_MouseDelta;
float Input::scrollDelta;
bool Input::mFocused = false;

bool Input::GetKeyDown(int glkeycode)
{
	if (glfwGetKey(Context::GetMainWindow(), glkeycode) == GLFW_PRESS)
	{
		auto iterator = std::find(m_heldKeyCache.begin(), m_heldKeyCache.end(), glkeycode);

		if (iterator == m_heldKeyCache.end())
		{
			m_heldKeyCache.push_back(glkeycode);
			return true;
		}
	}

	return false;
}

bool Input::GetKey(int glkeycode)
{
	int pressed = glfwGetKey(Context::GetMainWindow(), glkeycode);

	if (pressed == GLFW_PRESS)
		return true;

	return false;
}

glm::vec2 Input::GetMouseDelta()
{
	return m_MouseDelta;
}

void Input::LockCursor(bool state)
{
	if (state)
	{
		vec2 dimensions = Context::GetCurrentDimensions();
		glfwSetCursorPos(Context::GetMainWindow(), dimensions.x / 2, dimensions.y / 2);
		glfwSetInputMode(Context::GetMainWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	else
	{
		glfwSetInputMode(Context::GetMainWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
}

void Input::Update()
{
	scrollDelta = 0;
	glfwPollEvents();

	if (m_heldKeyCache.size() > 0)
	{
		for (unsigned int i = 0; i < m_heldKeyCache.size(); i++)
		{
			int keycode = m_heldKeyCache.at(i);
			if (glfwGetKey(Context::GetMainWindow(), keycode) == GLFW_RELEASE)
			{
				m_heldKeyCache.erase(m_heldKeyCache.begin() + i);
			}
		}
	}

	if (m_MouseCache.size() > 0)
	{
		for (unsigned int i = 0; i < m_MouseCache.size(); i++)
		{
			int button = m_MouseCache.at(i);
			if (glfwGetMouseButton(Context::GetMainWindow(), button) == GLFW_RELEASE)
			{
				m_MouseCache.erase(m_MouseCache.begin() + i);
			}
		}
	}

	
	double xpos, ypos;
	glfwGetCursorPos(Context::GetMainWindow(), &xpos, &ypos);

#pragma warning(push)
#pragma warning(disable: 4244)
	float xdelta = xpos - MouseX;
	float ydelta = ypos - MouseY;
#pragma warning(pop)

	m_MouseDelta.x = xdelta;
	m_MouseDelta.y = ydelta;
	MouseX = xpos;
	MouseY = ypos;
}

bool Input::GetMouseDown(int mouseButton)
{
	if (glfwGetMouseButton(Context::GetMainWindow(), mouseButton) == GLFW_PRESS)
	{
		auto iterator = std::find(m_MouseCache.begin(), m_MouseCache.end(), mouseButton);

		if (iterator == m_MouseCache.end())
		{
			m_MouseCache.push_back(mouseButton);
			return true;
		}
	}

	return false;
}

bool Input::GetMouse(int mouseButton)
{
	if (glfwGetMouseButton(Context::GetMainWindow(), mouseButton) == GLFW_PRESS)
		return true;

	return false;
}

glm::vec2 Input::GetMousePosition()
{
	return glm::vec2(MouseX, MouseY);
}

glm::vec2 Input::GetWASDVector()
{
	float forward = 0, side = 0;
	if (GetKey(GLFW_KEY_W) || GetKey(GLFW_KEY_UP))
	{
		forward += 1;
	}
	if (GetKey(GLFW_KEY_S) || GetKey(GLFW_KEY_DOWN))
	{
		forward -= 1;
	}
	if (GetKey(GLFW_KEY_D) || GetKey(GLFW_KEY_RIGHT))
	{
		side += 1;
	}
	if (GetKey(GLFW_KEY_A) || GetKey(GLFW_KEY_LEFT))
	{
		side -= 1;
	}

	if (forward == 0 && side == 0)
	{
		return glm::vec2(0, 0);
	}


	return vec2(side, forward);
}

glm::vec2 Input::GetWASDNormalized()
{
	float forward = 0, side = 0;
	if (GetKey(GLFW_KEY_W) || GetKey(GLFW_KEY_UP))
	{
		forward += 1;
	}
	if (GetKey(GLFW_KEY_S) || GetKey(GLFW_KEY_DOWN))
	{
		forward -= 1;
	}
	if (GetKey(GLFW_KEY_D) || GetKey(GLFW_KEY_RIGHT))
	{
		side += 1;
	}
	if (GetKey(GLFW_KEY_A) || GetKey(GLFW_KEY_LEFT))
	{
		side -= 1;
	}

	if (forward == 0 && side == 0)
	{
		return glm::vec2(0, 0);
	}


	return glm::normalize(vec2(side, forward));
}

vec2 Input::GetClampedMousePos()
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