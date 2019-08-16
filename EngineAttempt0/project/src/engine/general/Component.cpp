#include "Component.h"

void Component::UpdateComponent()
{
	if (!mActive)
		return;

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