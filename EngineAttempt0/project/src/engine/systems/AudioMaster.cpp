#include "AudioMaster.h"
 FMOD::System* AudioSystem::pSystem = nullptr;
 unsigned int AudioSystem::idPool = 0;
 std::unordered_map<unsigned int, FMOD::Sound*> AudioSystem::registeredSounds;
 std::vector<FMOD::Channel*> AudioSystem::playing;

unsigned int AudioSystem::RegisterAudio(FMOD::Sound* sound)
{
	unsigned int id = ++idPool;
	registeredSounds.insert(std::make_pair(id, sound));
	return id;
}

void AudioSystem::PlayOneShot3D(AudioClip clip, float volume, float pitch, vec3 position, vec3 velocity)
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

void AudioSystem::PlayOneShot(AudioClip clip, float volume, float pitch)
{
	FMOD::Channel* channel = nullptr;
	FMOD::Sound* sound = GetSound(clip.GetID());
	pSystem->playSound(sound, nullptr, true, &channel);

	channel->setVolume(volume);
	channel->setPitch(pitch);

	channel->setPaused(false);
}

FMOD::Sound* AudioSystem::GetSound(unsigned int id)
{
	if (registeredSounds.count(id) == 0)
		return nullptr;

	return registeredSounds[id];
}