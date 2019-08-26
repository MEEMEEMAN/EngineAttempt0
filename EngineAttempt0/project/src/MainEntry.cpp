#pragma once
#include "Core.h"

const int SCR_WIDTH = 1280, SCR_HEIGHT = 720;
const int fboResX = 1024, fboResY = 1024;
const char* title = "Perhaps?";
const std::string GLSL_VERSION = "#version 420 core";

int main()
{
	PerhapsApplication* application = new PerhapsApplication();
	application->Entry();

	delete(application);
	
	return 0;
}

//
//int main()
//{
//	
//	Application app;
//	app.Initialize(SCR_WIDTH, SCR_HEIGHT, title);
//	GUI::Initialize(GLSL_VERSION);
//
//	Loader loader;
//	AudioMaster audio;
//	audio.Init(32);
//	Loader::SetAudioMaster(&audio);
//
//	Component c1;
//	Component* c2 = c1.clone();
//
//	//SceneManager.LoadScene(sceneFilepath);
//#pragma region Asset Loading & Scene Building
//	GameObject camera;
//	camera.AddComponent(new Camera(65, SCR_WIDTH, SCR_HEIGHT));
//	camera.AddComponent(new AudioListener());
//	AudioClip swamp = loader.LoadAudio("project/assets/sfx/swampaha.wav", false);
//	camera.AddComponent(new AudioSource(swamp));
//	camera.AddComponent(new SwampClicker());
//
//	AudioClip lis = loader.LoadAudio("project/assets/sfx/lis.wav", true);
//	audio.PlayOneShot(lis, 1, 1);
//
//	Camera* camComponent = camera.GetComponent<Camera>();
//	MasterRenderer renderer(camComponent);
//	MeshRenderer::renderer = &renderer;
//
//	ShaderProgram* basicShader = new ShaderProgram("project/assets/shaders/basic.vert",
//		"project/assets/shaders/basic.frag");
//
//	TexturedMaterial wackmat(basicShader);
//	wackmat.AddTexture(loader.loadTexture("project/assets/models/wackterrain/wackterrain.png", true));
//
//	GameObject wackTerrain;
//	wackTerrain.AddComponent(
//		new MeshRenderer("project/assets/models/wackterrain/wackterrain.glb", &wackmat));
//	wackTerrain.transform.scale = vec3(0.1, 0.1, 0.1);
//
//	GLTexture boxTexture = loader.loadTexture("project/assets/textures/box.jpg", true);
//
//	TexturedMaterial cubeTexMat(basicShader);
//	cubeTexMat.AddTexture(boxTexture);
//	GameObject cubeObject;
//	cubeObject.AddComponent(new MeshRenderer("project/assets/models/sphere.glb", &cubeTexMat));
//	cubeObject.transform.position = vec3(0, 2, 2);
//
//	SkyboxRenderer skybox("project/assets/textures/spaceCubemap");
//	skybox.cam = camComponent;
//
//	ShaderProgram* uiShader = new ShaderProgram("project/assets/shaders/gui.vert", "project/assets/shaders/gui.frag");
//	TexturedMaterial refractionMat(uiShader);
//
//	FBO refractionBuffer(fboResX, fboResY);
//	refractionBuffer.GenTextureAttachment();
//	refractionBuffer.GenDepthTextureAttachment();
//	refractionMat.AddTexture(refractionBuffer.GetColorTexture());
//
//
//	TexturedMaterial reflectionMat(uiShader);
//
//	FBO reflectionBuffer(fboResX, fboResY);
//	reflectionBuffer.GenTextureAttachment();
//	reflectionBuffer.GenDepthTextureAttachment();
//	reflectionMat.AddTexture(reflectionBuffer.GetColorTexture());
//
//	/**
//		GameObject refractionSprite;
//		refractionSprite.AddComponent(new GUIRenderer(refractionMat));
//		refractionSprite.transform.scale = vec3(0.25, 0.25, 0);
//		refractionSprite.transform.position = vec3(-0.75, 0.75, 0);
//
//		GameObject reflectionSprite;
//		reflectionSprite.AddComponent(new GUIRenderer(reflectionMat));
//		reflectionSprite.transform.scale = vec3(0.25, 0.25, 0);
//		reflectionSprite.transform.position = vec3(0.75, 0.75, 0);
//		*/
//
//	ShaderProgram* waterShader = new ShaderProgram("project/assets/shaders/water.vert",
//		"project/assets/shaders/water.frag");
//	TexturedMaterial waterMat(waterShader);
//	waterMat.cullBackFace = false;
//	waterMat.AddTexture(reflectionBuffer.GetColorTexture(), "reflectTexture");
//	waterMat.AddTexture(refractionBuffer.GetColorTexture(), "refractTexture");
//	waterMat.AddTexture(loader.loadTexture("project/assets/textures/dudv.jpg", true), "dudvMap");
//	waterMat.AddTexture(loader.loadTexture("project/assets/textures/dudvNormal.png", true), "dudvNMap");
//	GameObject waterPlane;
//	waterPlane.AddComponent(new MeshRenderer("project/assets/models/plane.glb", &waterMat));
//	waterPlane.transform.scale *= 10;
//	waterPlane.transform.position = vec3(0, -0.4, 0);
//
//#pragma endregion
//
//
//	glfwSwapInterval(1);
//	glClearColor(0.3f, 0.3f, 1, 1);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CLIP_DISTANCE0);
//	glEnable(GL_CULL_FACE);
//
//
//	bool toggle = false;
//	bool toggleWireFrame = false;
//	bool vsyncBtn = true;
//	while (!Context::WindowShouldClose())
//	{
//
//		Time::Update();
//		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		GUI::BeginFrame();
//
//		static float rotation = 0;
//		rotation += 90 * Time::DeltaTime();
//		cubeObject.transform.rotaiton = vec3(rotation, rotation,0);
//
//
//		if (Input::GetKeyDown(GLFW_KEY_F1))
//		{
//			toggle = !toggle;
//			Input::LockCursor(toggle);
//		}
//		camera.Update();
//		vec3 camOriginalPos = camera.transform.position;
//		vec3 camOriginalRot = camera.transform.rotaiton;
//
//		
//		{ /* REFLECTION RENDER */
//			basicShader->RunProgram();
//			basicShader->SetUniform4f("plane", vec4(0,1,0, -waterPlane.transform.position.y));
//			
//			float distance = 2 * (camera.transform.position.y - waterPlane.transform.position.y);
//			camera.transform.position.y -=  distance;
//			camera.transform.rotaiton.x *= -1;
//			camera.UpdateTransform();
//			camComponent->CalcMatrix();
//
//			reflectionBuffer.Bind();
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			cubeObject.Update();
//			wackTerrain.Update();
//
//			renderer.InitiateRender();
//			skybox.Render();
//			reflectionBuffer.Unbind();
//
//			camera.transform.position = camOriginalPos;
//			camera.transform.rotaiton = camOriginalRot;
//			camComponent->CalcMatrix();
//		}
//
//		{ /* REFRACTION RENDER */
//			basicShader->RunProgram();
//			basicShader->SetUniform4f("plane", vec4(0,-1,0, waterPlane.transform.position.y));
//			refractionBuffer.Bind();
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			cubeObject.Update();
//			wackTerrain.Update();
//
//			renderer.InitiateRender();
//			skybox.Render();
//			refractionBuffer.Unbind();
//		}
//		FBO::Unbind();
//		
//		{ /* MAIN RENDER */
//			basicShader->RunProgram();
//			basicShader->SetUniform4f("plane", vec4(0,0,0,0));
//			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//			cubeObject.Update();
//			wackTerrain.Update();
//			waterPlane.Update();
//			renderer.InitiateRender();
//			skybox.Render();
//		}
//
//		waterShader->SetUniform3f("camPos", camera.transform.position);
//		waterShader->RunProgram();
//		waterShader->SetUniform1f("time", (float)Time::GetStartTimer());
//		skybox.Rotate();
//		//refractionSprite.Update();
//		//reflectionSprite.Update();
//
//		#pragma region ImGui
//
//		{
//			std::stringstream ss;
//			ImGui::Begin("Debug Info");
//
//			vec2 res = Input::GetScreenDimensions();
//			ss << "Current Resolution: " << res.x << "x" << res.y;
//			ImGui::Text(ss.str().c_str());
//			ss.str("");
//			std::string avgFPS = "Avg FPS: " + std::to_string(1/Time::GetAvgDelta());
//			ImGui::Text(avgFPS.c_str());
//			std::string avgDelta = "Avg Delta: " + std::to_string(Time::GetAvgDelta());
//			ImGui::Text(avgDelta.c_str());
//			ss << "CamPos: " << camera.transform.position;
//			ImGui::Text(ss.str().c_str());
//			bool btn = ImGui::Button("WireFrame");
//
//			if (btn)
//			{
//				toggleWireFrame = !toggleWireFrame;
//				
//				if(toggleWireFrame)
//					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//					else
//					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			}
//
//			bool vsync = ImGui::Button("Vsync");
//
//			if (vsync)
//			{
//				vsyncBtn = !vsyncBtn;
//
//				if(vsyncBtn)
//					glfwSwapInterval(1);
//				else
//					glfwSwapInterval(0);
//			}
//
//			ImGui::End();
//		}
//
//		#pragma endregion
//		
//		GUI::EndFrame();
//		Context::SwapBuffers();
//		Input::Update();
//		audio.Update();
//	}
//
//	Context::Terminate();
//
//	return 0;
//}
