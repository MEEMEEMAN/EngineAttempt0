#pragma once
#include "engine.h"
#include "WaterPlane.h"
#include "Skybox.h"
#include "SimpleMeshRenderer.h"

const int fboResX = 512, fboResY = 512;

class Scene1 : public Scene
{
public:
	
	Loader loader;
	void ConstructScene() override
	{

	vec2 dimensions = Input::GetScreenDimensions();
	GameObject* cameraObject = new GameObject();

	Camera* mainCam = new Camera(65, dimensions.x, dimensions.y);
	sceneCamera = mainCam;
	cameraObject->AddComponent(mainCam);
	cameraObject->AddComponent(new AudioListener());
	gameObjectRoots.push_back(cameraObject);

	ShaderProgram* shader = new ShaderProgram("game/assets/shaders/basic.vert", 
												"game/assets/shaders/basic.frag");

	TexturedMaterial* simpleMat = new TexturedMaterial(shader, "basic");
	simpleMat->AddTexture(loader.loadTexture("game/assets/textures/box.jpg", true), "image");


	GameObject* cube = new GameObject();
	cube->AddComponent(new SimpleMeshRenderer());
	gameObjectRoots.push_back(cube);

	
	GameObject* skyboxCube = new GameObject();
	skyboxCube->AddComponent(new Skybox());
	gameObjectRoots.push_back(skyboxCube);
	}
};