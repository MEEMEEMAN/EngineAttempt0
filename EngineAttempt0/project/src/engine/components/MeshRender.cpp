#include "..//rendering/MasterRenderer.h"
#include "MeshRender.h"

MasterRenderer* MeshRenderer::renderer = nullptr;

void MeshRenderer::Update()
{
	MasterRenderer::Instance()->SubmitRender(this, mat);
}