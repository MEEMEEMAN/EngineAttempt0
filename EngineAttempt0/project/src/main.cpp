#include "pch.h"
#include "engine/engine.h"

const int SCR_WIDTH = 1280, SCR_HEIGHT = 720;
const char* title = "Perhaps?";
const std::string GLSL_VERSION = "#version 420 core";


int main()
{

	if (!Context::CreateContext(SCR_WIDTH, SCR_HEIGHT, title))
	{
		return -1;
	}
	IMGUI::Initialize(GLSL_VERSION);

	std::vector<float> positions = 
	{
		-0.5f, -0.5f, 0,
		0.5f, -0.5f, 0,
		0.5f, 0.5f, 0,
		-0.5f, 0.5f, 0,
	};

	std::vector<unsigned int> indices
	{
		0,1,2,
		0,2, 3
	};
	
	Loader loader;
	RawModel model = loader.ImportSimpleModel("project/assets/models/cube.glb");//loader.Load(0,3,&positions, &indices);	

	ShaderProgram pg("project/src/engine/shaders/basic.vert", "project/src/engine/shaders/basic.frag");
	pg.RunProgram();
	Renderer renderer;

	mat4 projection = glm::perspective(glm::radians(65.0f),
			(float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 1000.0f);

	GLTexture texture;
	texture.LoadTexture2D("project/assets/textures/box.jpg", true);
	texture.BindTexture2D(0);

	Camera cam;

	glfwSwapInterval(1);
	glClearColor(0.3f, 0.3f, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	bool toggle = false;
	bool toggleWireFrame = false;
	while (!Context::WindowShouldClose())
	{
		Time::Update();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		IMGUI::BeginFrame();
		cam.Update();

		static float rotation = 0;
		rotation += 90 * Time::DeltaTime();
		mat4 modelMatrix = mat4(1);
		modelMatrix = glm::translate(modelMatrix, vec3(0,0, -1));
		modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), vec3(0,1,0));

		pg.SetMat4f("model", modelMatrix);
		pg.SetMat4f("projection", projection);
		pg.SetMat4f("view", cam.GetViewMatrix());

		if (Input::GetKeyDown(GLFW_KEY_F1))
		{
			toggle = !toggle;
			Input::LockCursor(toggle);
		}

		renderer.Draw(model);
		{
			ImGui::Begin("Debug Info");
			std::string avgFPS = "Avg FPS: " + std::to_string(1/Time::GetAvgDelta());
			ImGui::Text(avgFPS.c_str());
			bool btn = ImGui::Button("WireFrame");

			if (btn)
			{
				toggleWireFrame = !toggleWireFrame;
				
				if(toggleWireFrame)
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					else
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			ImGui::End();
		}
		
		IMGUI::EndFrame();
		Context::SwapBuffers();
		Input::Update();

	}

	Context::Terminate();

	return 0;
}
