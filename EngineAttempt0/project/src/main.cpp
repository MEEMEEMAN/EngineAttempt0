#include "pch.h"
#include "engine/engine.h"

const int SCR_WIDTH = 1280, SCR_HEIGHT = 720;
const char* title = "Perhaps?";
const std::string GLSL_VERSION = "#version 420 core";


int main()
{
	Application app;
	app.Initialize(SCR_WIDTH, SCR_HEIGHT, title);
	GUI::Initialize(GLSL_VERSION);

	/*
		ECS DEMO
	*/
	GameObject camera;
	camera.AddComponent(new Camera(65, SCR_WIDTH, SCR_HEIGHT));

	GameObject cubeObject;
	cubeObject.AddComponent(new MeshRenderer("project/assets/models/cube.glb"));
	
	Camera* camComponent = camera.GetComponent<Camera>();
	MasterRenderer renderer(camComponent);
	MeshRenderer::renderer = &renderer;

	/**/
	
	Loader loader;

	ShaderProgram pg("project/src/engine/shaders/basic.vert", "project/src/engine/shaders/basic.frag");
	Material basicMat(pg);

	GLTexture texture;
	texture.LoadTexture2D("project/assets/textures/box.jpg", true);
	texture.BindTexture2D(0);
	
	glfwSwapInterval(1);
	glClearColor(0.3f, 0.3f, 1, 1);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	//RawModel cube = loader.ImportSimpleModel("project/assets/models/cube.glb");

	bool toggle = false;
	bool toggleWireFrame = false;
	bool vsyncBtn = true;
	while (!Context::WindowShouldClose())
	{
		Time::Update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GUI::BeginFrame();

		static float rotation = 0;
		rotation += 90 * Time::DeltaTime();
		cubeObject.transform.rotaiton = vec3(rotation, rotation,0);


		if (Input::GetKeyDown(GLFW_KEY_F1))
		{
			toggle = !toggle;
			Input::LockCursor(toggle);
		}
		
		camera.Update();
		cubeObject.Update();

		renderer.InitiateRender();

		//glDrawElements(GL_TRIANGLES, cube.GetDrawCount(), GL_UNSIGNED_INT, 0);
		{
			std::stringstream ss;
			ImGui::Begin("Debug Info");
			std::string avgFPS = "Avg FPS: " + std::to_string(1/Time::GetAvgDelta());
			ImGui::Text(avgFPS.c_str());
			std::string avgDelta = "Avg Delta: " + std::to_string(Time::GetAvgDelta());
			ImGui::Text(avgDelta.c_str());
			ss << "CamPos: " << camComponent->position;
			ImGui::Text(ss.str().c_str());
			bool btn = ImGui::Button("WireFrame");

			if (btn)
			{
				toggleWireFrame = !toggleWireFrame;
				
				if(toggleWireFrame)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			bool vsync = ImGui::Button("Vsync");

			if (vsync)
			{
				vsyncBtn = !vsyncBtn;

				if(vsyncBtn)
					glfwSwapInterval(1);
				else
					glfwSwapInterval(0);
			}

			ImGui::End();
		}
		
		GUI::EndFrame();
		Context::SwapBuffers();
		Input::Update();

	}

	Context::Terminate();

	return 0;
}
