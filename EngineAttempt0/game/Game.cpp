#pragma once
#include "..//project/src/Core.h"
#include "components/Scene1.h"

class Game
{
public:

	const int SCR_WIDTH = 1280, SCR_HEIGHT = 720;
	const char* title = "Perhaps?";
	
	void Begin()
	{
		context = new Context();
		
		/*
		* Ideally we would read a config file from previous launches with-
		user saved screen dimension values.
		*/
		context->CreateContext(SCR_WIDTH, SCR_HEIGHT, "Perhaps Game");

		Initialization();
		UpdateLoop();

		delete(context);
	}

	const std::string GLSL_VERSION = "#version 420 core";

	void Initialization()
	{
		Input::Initialize();
		ImmediateGUI::Initialize(GLSL_VERSION);

		RenderSystem::Initialize(nullptr);
		AudioSystem::Initialize(32);

		Scene1* scene = new Scene1();
		scene->ConstructScene();

		RenderSystem::SetRenderCam(scene->GetMainCamera());
		SceneManager::SetSceneAsCurrent(scene);
		scene->StartRootGameObjects();
	}

	void UpdateLoop()
	{
		glClearColor(0.2,0.2,0.7,1);
		glEnable(GL_CLIP_DISTANCE0);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		bool cursorToggle = false;

		while (!context->WindowShouldClose())
		{
			ImmediateGUI::BeginFrame();
			Time::Update();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			SceneManager::SceneUpdate();


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
			RenderSystem::BeginRender(SceneManager::GetCurrentScene()->GetMainCamera());
			SceneManager::PostRenderUpdate();

			RenderSystem::ClearRenderBuffer();

			ImmediateGUI::Render();
			AudioSystem::Update();
			ImmediateGUI::EndFrame();

			Context::SwapBuffers();
			Input::Update();
		}

		Cleanup();
	}


	void Cleanup()
	{
		SceneManager::CleanUp();
		ImmediateGUI::CleanUp();
		Material::CleanUp();
		AudioSystem::CleanUp();
		context->Terminate();
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
