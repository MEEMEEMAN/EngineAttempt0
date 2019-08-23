#pragma once
#include "pch.h"
#include "GLObject.h"

class GLCubeMap : public GLObject
{
	public:

	GLCubeMap()
	{
		
	}

	GLCubeMap(unsigned int cubeID)
	{
		mID = cubeID;
	}

	void BindCubemap(unsigned int slot)
	{
		slot = GL_TEXTURE0 + slot;

		if (slot < GL_TEXTURE0 || slot > GL_TEXTURE29)
		{
			conlog("invalid slot.");
			return;
		}

		glActiveTexture(slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mID);
	}
};