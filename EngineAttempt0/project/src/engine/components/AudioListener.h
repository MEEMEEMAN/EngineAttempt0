#pragma once
#include "pch.h"
#include "..//general/Component.h"
#include "..//general/GameObject.h"
#include "..//systems/AudioMaster.h"

class AudioListener : public Component
{
	public:

	void Start() override
	{
		prevPos = owner->transform.position;
	}

	void Update() override
	{
		fmodvec pos, forward, up, vel;
		pos = owner->transform.position;
		forward = owner->transform.GetForward();
		up = owner->transform.GetUp();

		vec3 velocity = owner->transform.position - prevPos;
		vel = velocity;

		prevPos = owner->transform.position;

		AudioSystem::GetSystem()->
		set3DListenerAttributes(0, &pos, &vel, &forward, &up);
	}

	auto clone() const -> Component* override
	{
		return new AudioListener(*this);
	}

	protected:
	std::string GetID() const override
	{
		return "AudioListener";
	}

	private:
	vec3 prevPos = vec3(0);
};