#include "Renderer.h"

void Renderer::Draw(RawModel model)
{
	model.Bind();

	if (model.HasIndices())
	{
		glDrawElements(GL_TRIANGLES, model.GetDrawCount(), GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, model.GetDrawCount());
	}

}