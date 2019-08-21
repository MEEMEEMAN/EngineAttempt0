#pragma once
#include "pch.h"
#include "RawModel.h"
#include "ModelImporter.h"
#include "GLCube.h"
#include "Image.h"
#include "..//general/AudioMaster.h"

class Loader
{
	public:
	static void SetAudioMaster(AudioMaster* master)
	{
		audioMaster = master;
	}

	AudioClip LoadAudio(std::string filepath, bool stream)
	{
		FMOD::Sound* pSound = nullptr;

		if (stream)
		{
			audioMaster->GetSystem()->createStream(filepath.c_str(), FMOD_3D, nullptr, &pSound);
		}
		else
		{
			audioMaster->GetSystem()->createSound(filepath.c_str(), FMOD_3D, nullptr, &pSound);
		}

		unsigned int soundID = audioMaster->RegisterAudio(pSound);
		AudioClip file(soundID, filepath);

		return file;
	}

	//Load a rawmodel with only position data.
	RawModel Load(unsigned int index ,unsigned int dimensions,std::vector<float>* positions);

	RawModel Load(unsigned int index, std::vector<vec3>* positions);
	
	//Load a rawmodel with position and draw index data.
	RawModel Load(unsigned int index, unsigned int dimensions, 
				std::vector<float> * positions, std::vector<unsigned int>* indices);

	RawModel Load(std::vector<vec3>* positions, std::vector<vec2>* uvs);

	RawModel Load(std::vector<vec3>* positions, std::vector<vec2>* uvs, std::vector<unsigned int>* indices);

	GLTexture loadTexture(std::string filepath, bool flipVertically);

	/*
	* You must provide the directory which all of your images reside.
	* this function is going to search for the following image names in the following order:
	right.png, left.png, top.png, bottom.png, front.png, back.png
	*/
	GLCube LoadCubemap(std::string directory);

	//Load a rawmodel with position and draw index data.

/*
* loads a 3d model from the specified filepath.
* supports only single meshed models.
* shader locations are as follows:
	vec3 positions = 0
	vec2 uvs = 1
	vec3 normals 2
	vec3 tangents = 3
	vec3 biTangets = 4
*/
	RawModel ImportSimpleModel(std::string filepath);

	private:
	static AudioMaster* audioMaster;
	ModelImporter importer;

	//Generate a vertex array and return the id.
	unsigned int GenVAO();

	//Implementation of loading data.
	void LoadData(unsigned int index, unsigned int dimensions, std::vector<float>* positions);
	void LoadData(unsigned int index, std::vector<vec3>* positions);
	void LoadData(unsigned int index, std::vector<vec2>* positions);

	RawModel LoadModel(std::vector<vec3>* positions, std::vector<unsigned int>* indices,
		std::vector<vec2>* uvs, std::vector<vec3>* normals,
		std::vector<vec3>* tangents, std::vector<vec3>* biTangents);

	//Implementation of index buffer loading, returns the id to said buffer.
	unsigned int LoadIndices(std::vector<unsigned int>* indices);

	const std::vector<std::string> faces = 
	{
	"right.png",
	"left.png",
	"top.png",
	"bottom.png",
	"front.png",
	"back.png"
	};
};