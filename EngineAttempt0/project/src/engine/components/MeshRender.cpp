#include "..//rendering/MasterRenderer.h"
#include "MeshRender.h"

MasterRenderer* MeshRenderer::renderer = nullptr;

void MeshRenderer::Update()
{
	renderer->SubmitRender(this, mat);
}