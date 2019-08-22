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


class AudioMaster
{
	public:

	/*
	* Initializes the Audio engine.
	* AudioMaster acts as a singleton, where only 1 instance of it can exist. this
	instance can be returned via the Instance function.
	*/
	void Init(int maxChannelCount)
	{
		FMOD::System_Create(&pSystem);
		pSystem->init(maxChannelCount, FMOD_INIT_NORMAL, nullptr);

		instance = this;
	}

	/*
	* Registers an AudioClip and returns it's id.
	* AudioClips that were not registered cannot be played.
	* AudioClips can be loaded via the Loader.
	*/
	unsigned int RegisterAudio(FMOD::Sound* sound);

	/*
	* Plays a single AudoClip playback in 3d space.
	*/
	void PlayOneShot3D(AudioClip clip, float volume, float pitch, vec3 position, vec3 velocity);

	/*
	* Plays a single AudioClip in 2D space.
	*/
	void PlayOneShot(AudioClip clip, float volume, float pitch);

	/*
	* Updates the Audio engine.
	*/
	void Update()
	{
		pSystem->update();
	}

	static void UpdateInstance()
	{
		instance->Update();
	}

	/*
	* Returns FMOD's system component.
	*/
	inline FMOD::System* GetSystem() const
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
	/*
	* Returns a singleton instance of the AudioMaster.
	*/

	static AudioMaster* Instance()
	{
		return instance;
	}

	private:
	/*
	* Get a sound from the registeredSounds map.
	* Returns null if the id is invalid.
	*/
	FMOD::Sound* GetSound(unsigned int id);

	FMOD::System* pSystem = nullptr;
	static unsigned int idPool;
	std::unordered_map<unsigned int, FMOD::Sound*> registeredSounds; 
	std::vector<FMOD::Channel*> playing;
	static AudioMaster* instance;
};