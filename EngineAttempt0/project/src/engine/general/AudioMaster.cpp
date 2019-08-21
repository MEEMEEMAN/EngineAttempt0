#include "AudioMaster.h"

unsigned int AudioMaster::idPool = 0;
AudioMaster* AudioMaster::instance = nullptr;

unsigned int AudioMaster::RegisterAudio(FMOD::Sound* sound)
{
	unsigned int id = ++idPool;
	registeredSounds.insert(std::make_pair(id, sound));
	return id;
}

void AudioMaster::PlayOneShot3D(AudioClip clip, float volume, float pitch, vec3 position, vec3 velocity)
{
	FMOD::Channel* channel = nullptr;
	FMOD::Sound* sound = GetSound(clip.GetID());
	pSystem->playSound(sound, nullptr, true, &channel);

	channel->setVolume(volume);
	channel->setPitch(pitch);

	fmodvec fmodPos;
	fmodPos = position;
	fmodvec fmodVel;
	fmodVel = velocity;

	channel->set3DAttributes(&fmodPos, &fmodVel);

	channel->setPaused(false);
}

void AudioMaster::PlayOneShot(AudioClip clip, float volume, float pitch)
{
	FMOD::Channel* channel = nullptr;
	FMOD::Sound* sound = GetSound(clip.GetID());
	pSystem->playSound(sound, nullptr, true, &channel);

	channel->setVolume(volume);
	channel->setPitch(pitch);

	channel->setPaused(false);
}

FMOD::Sound* AudioMaster::GetSound(unsigned int id)
{
	if (registeredSounds.count(id) == 0)
		return nullptr;

	return registeredSounds[id];
}