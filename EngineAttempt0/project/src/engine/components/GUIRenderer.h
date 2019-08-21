#pragma once
#include "pch.h"
#include "..//materials/TexturedMat.h"
#include "..//general/Component.h"
#include "..//rendering/Loader.h"
#include "..//general/Time.h"
#include "..//general/GameObject.h"

class GUIRenderer : public Component
{
	public:

	GUIRenderer(TexturedMaterial texmat)
	{
		Loader loader;
		std::vector<vec3> tempPos = positions;
		std::vector<vec2> tempUvs = uvs;
		std::vector<unsigned int> tempIndex = indices;
		uiModel = loader.Load(&tempPos, &tempUvs, &tempIndex);
		texturedMat = texmat;
	}

	void Update() override
	{
		uiModel.Bind();
		texturedMat.Bind();
		texturedMat.ApplyMaterial();

		texturedMat.GetShader()->SetMat4f("model", owner->transform.GetModel());

		glDrawElements(GL_TRIANGLES, uiModel.GetDrawCount(), GL_UNSIGNED_INT, 0);
	}

	private:
	mat4 mProjection;
	RawModel uiModel;
	TexturedMaterial texturedMat;
	const std::vector<vec3> positions = 
	{
		vec3(-1, -1, 0), //bottom left
		vec3(1, -1, 0), //bottom right
		vec3(1,1, 0), //top right
		vec3(-1, 1, 0), //top left
	};
	const std::vector<vec2> uvs = 
	{
		/*
		vec2(0,1),
		vec2(1,1),
		vec2(1,0),
		vec2(0,0)
		*/

		
		vec2(0,0),
		vec2(1, 0),
		vec2(1,1),
		vec2(0, 1)
		
	};
	const std::vector<unsigned int> indices
	{
		0,1,2,
		0,2,3
	};
};