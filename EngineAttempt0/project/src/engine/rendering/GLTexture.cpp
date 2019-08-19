#pragma once
#include "GLTexture.h"

void GLTexture::BindTexture2D(unsigned int slot)
{
	slot = GL_TEXTURE0 + slot;

	if (slot < GL_TEXTURE0 || slot > GL_TEXTURE29)
	{
		conlog(slot - GL_TEXTURE0 << " slot is invalid.");
		return;
	}

	glActiveTexture(slot);
	glBindTexture(GL_TEXTURE_2D, mID);
}
