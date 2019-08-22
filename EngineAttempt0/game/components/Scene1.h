#pragma once
#include "engine.h"
#include "WaterPlane.h"

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

	AudioClip shrekGasm = loader.LoadAudio("game/assets/sfx/swampaha.wav", false);

	cameraObject->AddComponent(new AudioListener());
	cameraObject->AddComponent(new AudioSource(shrekGasm));
	cameraObject->AddComponent(new SwampClicker());
	gameObjectRoots.push_back(cameraObject);

	GameObject* wackTerrain = new GameObject();

	ShaderProgram* shaderProgram = new ShaderProgram("game/assets/shaders/basic.vert", 
													"game/assets/shaders/basic.frag");

	TexturedMaterial* wackMat = new TexturedMaterial(shaderProgram, "basicMat");
	wackMat->AddTexture(loader.loadTexture("game/assets/models/wackterrain/wackterrain.png", true));
	wackTerrain->AddComponent(new MeshRenderer("game/assets/models/wackterrain/wackterrain.glb", wackMat));
	wackTerrain->transform.scale = vec3(0.1, 0.1, 0.1);

	gameObjectRoots.push_back(wackTerrain);


	GameObject* lisPlayer = new GameObject();

	AudioSource* src = new AudioSource(loader.LoadAudio("game/assets/sfx/lis.wav", true));
	src->PlayOneShot(0.5f);
	lisPlayer->AddComponent(src);
	gameObjectRoots.push_back(lisPlayer);

	GameObject* water = new GameObject();
	water->AddComponent(new WaterPlane());
	water->transform.scale *= 10;
	water->transform.position = vec3(0, -0.4, 0);
	gameObjectRoots.push_back(water);

	}
};