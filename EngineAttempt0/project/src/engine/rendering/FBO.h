#pragma once
#include "pch.h"
#include "GLObject.h"
#include "GLTexture.h"

class FBO : public GLObject
{
	public:
	FBO(float resolutionX, float resolutionY)
	{
		fboWidth = resolutionX;
		fboHeight = resolutionY;
		GenFBO();
	}

	FBO()
	{

	}

	bool FBOComplete()
	{
		Bind();
		bool value = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
		Unbind();
		return value;
	}

	void GenFBO()
	{
		glGenFramebuffers(1, &mID);
	}

	void Bind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, mID);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
		glViewport(0,0, fboWidth, fboHeight);
	}

	void GenTextureAttachment()
	{
		Bind();
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fboWidth, fboHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
		textureAttach = GLTexture(textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,textureID, 0);
		Unbind();
	}

	void GenDepthTextureAttachment()
	{
		Bind();
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32
				, fboWidth, fboHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, (void*)0);
		depthTexture = GLTexture(textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, textureID, 0);
		Unbind();
	}
	/*
	void GenDepthBufferAttachment()
	{
		Bind();
		glGenRenderbuffers(1, &renderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fboWidth, fboHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, 
			GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
		Unbind();
	}
	*/
	static void Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		vec2 dimensions = Input::GetScreenDimensions();
		glViewport(0,0, dimensions.x, dimensions.y);
	}

	inline GLTexture GetColorTexture()
	{
		return textureAttach;
	}

	inline GLTexture GetDepthTexture()
	{
		return depthTexture;
	}

	private:
	float fboWidth = 0, fboHeight = 0;
	vec2 bufferDimensions = vec2(0);
	GLTexture textureAttach, depthTexture;
	unsigned int renderBuffer = 0;

};