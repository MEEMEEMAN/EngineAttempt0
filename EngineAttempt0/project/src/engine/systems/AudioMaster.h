#pragma once
#include "pch.h"

/*
* AudioClip class keeps an id number and a filepath for the loaded audio data.
*/
class AudioClip
{
	public:

	/*
	* This constructor should only really be used by the Loader.
	*/
	AudioClip(unsigned int id, std::string filepath)
	{
		audioID = id;
		filePath = filepath;
	}

	AudioClip() {};

	unsigned int GetID()
	{
		return audioID;
	}

	std::string GetFilepath()
	{
		return filePath;
	}

	private:
	unsigned int audioID = 0;
	std::string filePath = "";
};


class AudioSystem
{
	public:

	/*
	* Initializes the Audio engine.
	* maxChannelCount reffers to the maximum allowed audio channels to play at one time.
	*/
	static void Initialize(int maxChannelCount)
	{
		FMOD::System_Create(&pSystem);
		pSystem->init(maxChannelCount, FMOD_INIT_NORMAL, nullptr);
	}

	/*
	* Registers an AudioClip and returns it's id.
	* AudioClips that were not registered cannot be played.
	* AudioClips can be loaded via the Loader.
	*/
	static unsigned int RegisterAudio(FMOD::Sound* sound);

	/*
	* Plays a single AudoClip playback in 3d space.
	*/
	static void PlayOneShot3D(AudioClip clip, float volume, float pitch, vec3 position, vec3 velocity);

	/*
	* Plays a single AudioClip in 2D space.
	*/
	static void PlayOneShot(AudioClip clip, float volume, float pitch);

	/*
	* Updates the Audio engine.
	*/
	static void Update()
	{
		pSystem->update();
	}

	/*
	* Returns FMOD's system component.
	*/
	static inline FMOD::System* const GetSystem()
	{
		return pSystem;
	}

	/*
	* Returns an AudioClip id number that is registry ready.
	* Does not consume the id, it is only consumed when actually loading a file via the Loader.
	*/
	inline unsigned int GetAvailableID() const
	{
		return idPool + 1;
	}

	static void CleanUp()
	{
		pSystem->close();
	}

	private:
	/*
	* Get a sound from the registeredSounds map.
	* Returns null if the id is invalid.
	*/
	static FMOD::Sound* GetSound(unsigned int id);
	static FMOD::System* pSystem;
	static unsigned int idPool;
	static std::unordered_map<unsigned int, FMOD::Sound*> registeredSounds; 
	static std::vector<FMOD::Channel*> playing;
};