#pragma once
#include "pch.h"
#include "..//general/GameObject.h"
#include "..//general/Component.h"
#include "AudioSource.h"
#include "..//Input.h"

class SwampClicker : public Component
{
	public:

	void Start() override
	{
		src = owner->GetComponent<AudioSource>();
	}

	void Update() override
	{
		if (Input::GetMouseDown(0))
		{
			src->PlayOneShot(1.0f);
		}
	}

	private:
	AudioSource* src = 0;
};