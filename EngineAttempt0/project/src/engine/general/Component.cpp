#pragma once
#include "Component.h"

void Component::UpdateComponent()
{
	Update();
}

void Component::PreRenderUpdate()
{
	PreRender();
}

void Component::UpdatePostRender()
{
	PostRender();
}

void Component::StartComponent()
{
	Start();
}

void Component::Destroy()
{
	delete(this);
}