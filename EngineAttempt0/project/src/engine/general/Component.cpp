#pragma once
#include "Component.h"

void Component::UpdateComponent()
{
	Update();
}

void Component::StartComponent()
{
	Start();
}

void Component::Destroy()
{
	delete(this);
}