#pragma once
#include "engine.h"

class WaterPlane : public Renderable
{
	const float resX  = 512, resY = 512;
	public:

	void Start() override
	{
		SetModel(loader.ImportSimpleModel("game/assets/models/plane.glb"));
		basicMaterial = dynamic_cast<TexturedMaterial*>(Material::GetMaterial("basicMat"));

		ShaderProgram* waterShader = new ShaderProgram("game/assets/shaders/water.vert", 
														"game/assets/shaders/water.frag");
		planeMat = new TexturedMaterial(waterShader, "planeMat");
		planeMat->cullBackFace = false;

		mainCam = SceneManager::GetCurrentScene()->GetMainCamera();
		refractionBuffer = new FBO(resX, resY);
		refractionBuffer->GenTextureAttachment();
		refractionBuffer->GenDepthTextureAttachment();


		reflectionBuffer = new FBO(resX, resY);
		reflectionBuffer->GenTextureAttachment();
		reflectionBuffer->GenDepthTextureAttachment();

		planeMat->AddTexture(reflectionBuffer->GetColorTexture(), "reflectTexture");
		planeMat->AddTexture(refractionBuffer->GetColorTexture(), "refractTexture");

		planeMat->AddTexture(loader.loadTexture("game/assets/textures/dudv.jpg", true), "dudvMap");
		planeMat->AddTexture(loader.loadTexture("game/assets/textures/dudvNormal.png", true), "dudvNMap");

		//plane->mat = planeMat;
	}

	void Update() override
	{
		//need to override MeshRenderer's update.
	}

	void PreRender() override
	{

		{ /* REFLECTION RENDER */
			vec3 camOriginalPos = mainCam->owner->transform.position;
			vec3 camOriginalRot = mainCam->owner->transform.rotaiton;

			basicMaterial->GetShader()->SetUniform4f("plane", vec4(0, 1, 0, -owner->transform.position.y));
			float distance = 2 * (mainCam->owner->transform.position.y - owner->transform.position.y);
			
			mainCam->owner->transform.position.y -= distance;
			mainCam->owner->transform.rotaiton.x *= -1;
			mainCam->owner->UpdateTransform();
			mainCam->CalcMatrix();
			
			reflectionBuffer->Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//MasterRenderer::BeginRender(mainCam);
			RenderSystem::BeginRender();

			mainCam->owner->transform.position = camOriginalPos;
			mainCam->owner->transform.rotaiton = camOriginalRot;

			mainCam->CalcMatrix();
			FBO::Unbind();
		}

		{ /* REFRACTION RENDER */
			basicMaterial->GetShader()->SetUniform4f("plane", vec4(0,-1,0, owner->transform.position.y));
			refractionBuffer->Bind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			RenderSystem::BeginRender();
			FBO::Unbind();
		}

		basicMaterial->GetShader()->SetUniform4f("plane", vec4(0, 0, 0, 0));
		planeMat->GetShader()->SetUniform3f("camPos", mainCam->owner->transform.position);
		planeMat->GetShader()->SetUniform1f("time", (float)Time::GetStartTimer());
		//MasterRenderer::Instance()->SubmitRender(this, planeMat);
		RenderSystem::SubmitRender(*this);
	}

	private:
	Loader loader;
	TexturedMaterial* planeMat = nullptr;
	TexturedMaterial* basicMaterial = nullptr;
	Camera* mainCam = nullptr;
	FBO* refractionBuffer = nullptr;
	FBO* reflectionBuffer = nullptr;
};