#pragma once
#include "pch.h"
#include "GLObject.h"
#include "Image.h"

class GLTexture : public GLObject
{
	public:

	GLTexture(unsigned int id)
	{
		mID =id;
	}

	GLTexture()
	{

	}

	static void Unbind()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	void BindTexture2D(unsigned int slot);

	private:
};