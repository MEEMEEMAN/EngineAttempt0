#pragma once
#include "pch.h"
#include "engine.h"
#include "SceneManager.h"

class ImmediateGUI
{
	public:

	//Initializes IMGUI
	static void Initialize(std::string GLSL_VERSION);

	//Runs all start of frame IMGUI code.
	static void BeginFrame();

	//Runs all end of frame IMGUI code.
	static void EndFrame();

	static bool toggle, toggleWireFrame, vsyncBtn;

	static void Render()
	{
		
			std::stringstream ss;
			ImGui::Begin("Debug Info");

			vec2 res = Input::GetScreenDimensions();
			ss << "Current Resolution: " << res.x << "x" << res.y;
			ImGui::Text(ss.str().c_str());
			ss.str("");
			std::string avgFPS = "Avg FPS: " + std::to_string(1 / Time::GetAvgDelta());
			ImGui::Text(avgFPS.c_str());
			std::string avgDelta = "Avg Delta: " + std::to_string(Time::GetAvgDelta());
			ImGui::Text(avgDelta.c_str());
			vec3 camPos = SceneManager::GetCurrentScene()->GetMainCamera()->owner->transform.position;
			ss << "CamPos: " << camPos;
			ImGui::Text(ss.str().c_str());
			bool btn = ImGui::Button("WireFrame");

			if (btn)
			{
				toggleWireFrame = !toggleWireFrame;

				if (toggleWireFrame)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			bool vsync = ImGui::Button("Vsync");

			if (vsync)
			{
				vsyncBtn = !vsyncBtn;

				if (vsyncBtn)
					glfwSwapInterval(1);
				else
					glfwSwapInterval(0);
			}

			ImGui::End();
		
	}

	private:
};