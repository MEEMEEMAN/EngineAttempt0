#pragma once
#include "pch.h"
#include "systems/AudioMaster.h"
#include "..//general/Component.h"
#include "..//general/GameObject.h"

class AudioSource : public Component
{
	public:
	AudioSource(AudioClip clip)
	{
		SetClip(clip);
	}

	void Start() override
	{
		prevPos = owner->transform.position;
	}
	
	AudioSource()
	{
		
	}

	void PlayOneShot(float volume)
	{
		AudioSystem::PlayOneShot(currentClip, volume, pitch);
	}

	void PlayOneShot(AudioClip clip, float volume)
	{
		vec3 velocity = owner->transform.position - prevPos;
		prevPos = owner->transform.position;

		AudioSystem::PlayOneShot3D(clip, volume, pitch, owner->transform.position, velocity);
	}

	void SetClip(AudioClip clip)
	{
		currentClip = clip;
	}

	float pitch = 1;
	protected:
	AudioClip currentClip;

	private:
	vec3 prevPos = vec3(0);
};