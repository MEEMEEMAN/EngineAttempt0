#pragma once
#include "..//project/src/Core.h"
#include "components/Scene1.h"

class Game
{
public:
	
	void Begin()
	{
		context = new Context();

		/*
		* Ideally we would read a config file from previous launches with-
		user saved screen dimension values.
		*/
		context->CreateContext(1280, 720, "Perhaps Game");



		Initialization();
		UpdateLoop();
	}

	const int SCR_WIDTH = 1280, SCR_HEIGHT = 720;
	const char* title = "Perhaps?";
	const std::string GLSL_VERSION = "#version 420 core";

	void Initialization()
	{
		Input::Initialize();
		ImmediateGUI::Initialize(GLSL_VERSION);

		MasterRenderer* renderer = new MasterRenderer();
		renderer->SetInstance(renderer);
		
		AudioMaster* audioMaster = new AudioMaster();
		audioMaster->Init(32);

		Scene1* scene = new Scene1();
		scene->ConstructScene();

		SceneManager::SetSceneAsCurrent(scene);
		scene->StartRootGameObjects();
	}

	void UpdateLoop()
	{
		glClearColor(0.2,0.2,0.7,1);
		glEnable(GL_CLIP_DISTANCE0);
		glEnable(GL_DEPTH_TEST);
		bool cursorToggle = false;

		while (!context->WindowShouldClose())
		{
			ImmediateGUI::BeginFrame();
			Time::Update();
			SceneManager::SceneUpdate();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			if (Input::GetKeyDown(GLFW_KEY_F1))
			{
				cursorToggle = !cursorToggle;

				if (cursorToggle)
				{
					Input::CursorLock(true);
				}
				else
				{
					Input::CursorLock(false);
				}
			}

			SceneManager::PreRenderUpdate();
			MasterRenderer::BeginRender(SceneManager::GetCurrentScene()->GetMainCamera());
			SceneManager::PostRenderUpdate();
			MasterRenderer::ClearQueue();

			ImmediateGUI::Render();
			AudioMaster::UpdateInstance();
			ImmediateGUI::EndFrame();
			Context::SwapBuffers();
			Input::Update();
		}

		Cleanup();
	}

	void Cleanup()
	{
		MasterRenderer::Cleanup();
	}


private:
	Context* context = nullptr;
	Loader assetLoader;
	std::map<std::string, Component*> componentPool;
};


void PerhapsApplication::Entry()
{
	Game* game = new Game();
	game->Begin();

	delete(game);

	return;
}
