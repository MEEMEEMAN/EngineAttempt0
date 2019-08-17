#pragma once
#include "pch.h"
#include "GLObject.h"
#include "Image.h"

class GLTexture : public GLObject
{
	public:

	void LoadTexture2D(std::string filepath, bool flipVertically);


	void BindTexture2D(unsigned int slot);

	private:
};