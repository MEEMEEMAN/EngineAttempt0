#include "RawModel.h"

RawModel::RawModel(unsigned int vaoID, unsigned int eboID, unsigned int drawCount)
{
	mVAO = vaoID;
	mEBO = eboID;
	mDrawCount = drawCount;
}

void RawModel::Bind()
{
	glBindVertexArray(mVAO);

	if (HasIndices())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	}
}