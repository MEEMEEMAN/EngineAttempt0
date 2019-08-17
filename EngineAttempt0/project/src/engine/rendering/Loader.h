#pragma once
#include "pch.h"
#include "RawModel.h"
#include "ModelImporter.h"
#include "GLCube.h"
#include "Image.h"

class Loader
{
	public:
	//Load a rawmodel with only position data.
	RawModel Load(unsigned int index ,unsigned int dimensions,std::vector<float>* positions);

	RawModel Load(unsigned int index, std::vector<vec3>* positions);
	
	//Load a rawmodel with position and draw index data.
	RawModel Load(unsigned int index, unsigned int dimensions, 
				std::vector<float> * positions, std::vector<unsigned int>* indices);

	/*
	* You must provide the directory which all of your images reside.
	* this function is going to search for the following image names in the following order:
	right.png, left.png, top.png, bottom.png, front.png, back.png
	*/
	GLCube LoadCubemap(std::string directory)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		for (size_t i = 0; i < 6; i++)
		{
			std::stringstream path;
			path << directory << "/" << faces[i];
			Image face(path.str(), true);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGBA, face.GetImageWidth(), 
				face.GetImageHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, face.GetImageData());
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

		return GLCube(textureID);
	}

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