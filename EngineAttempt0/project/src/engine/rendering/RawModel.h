#pragma once
#include "pch.h"

class RawModel
{
	public:
	/*
	* A RawModel has to be loaded with the Loader class. it takes care of generating the
	  vaoID, eboID and drawcount.
	*/
	RawModel(unsigned int vaoID, unsigned int eboID, unsigned int drawCount);

	/*
	* Called via Renderer class when it's about to draw the RawModel.
	* This call binds the respective vertex-array-object and element-array-object to be used for drawing.
	*/
	void Bind();

	inline unsigned int GetVAO()
	{
		return mVAO;
	}

	inline unsigned int GetDrawCount()
	{
		return mDrawCount;
	}

	inline unsigned int GetEBO()
	{
		return mEBO;
	}

	inline bool HasIndices()
	{
		return mEBO > 0 ? true : false;
	}

	private:
		unsigned int mVAO = 0, mEBO = 0, mDrawCount = 0;
};