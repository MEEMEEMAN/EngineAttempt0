#pragma once
#include "GLTexture.h"

void GLTexture::LoadTexture2D(std::string filepath, bool flipVertically = true)
{
	Image image(filepath, true);

	GLuint format = GL_RGB;
	switch (image.PixelChannels())
	{
	case 3:
		format = GL_RGB;
		break;
		format = GL_RGBA;
	case 4:
		break;
	default:
		conlog("UnSupported image format?");
		return;
	}

	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	glTexImage2D(GL_TEXTURE_2D, 0, format, image.GetImageWidth(), image.GetImageHeight(), 0,
		format, GL_UNSIGNED_BYTE, image.GetImageData());

	glGenerateMipmap(GL_TEXTURE_2D);
}

void GLTexture::BindTexture2D(unsigned int slot)
{
	slot = GL_TEXTURE0 + slot;

	if (slot < GL_TEXTURE0 || slot > GL_TEXTURE29)
	{
		conlog("invalid slot.");
		return;
	}

	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, slot);
}
