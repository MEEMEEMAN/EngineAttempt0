#pragma once
#include "pch.h"
#include "RawModel.h"
#include "ModelImporter.h"

class Loader
{
	public:
	//Load a rawmodel with only position data.
	RawModel Load(unsigned int index ,unsigned int dimensions,std::vector<float>* positions);
	
	//Load a rawmodel with position and draw index data.
	RawModel Load(unsigned int index, unsigned int dimensions, 
				std::vector<float> * positions, std::vector<unsigned int>* indices);

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
};