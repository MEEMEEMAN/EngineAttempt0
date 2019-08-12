#pragma once
#include "pch.h"

struct GLMesh
{
	std::vector<unsigned int> indices;
	std::vector<vec3> Positions;
	std::vector<vec2> UVs;
	std::vector<vec3> Normals;
	std::vector<vec3> tangents;
	std::vector<vec3> biTangents;
};


class ModelImporter
{
public:

	ModelImporter()
	{
	}

	unsigned int totalVertexCount = 0;
	GLMesh* Import(std::string filepath);

private:
	/*
	* Returns whether or not the file provided via the filepath exists.
	*/
	bool fileExists(std::string file);

	/*
	* Used for seralizing the importer file into a grab-and-go ready format.
	* This is opposed to having to load and parse the file with assimp every time i want to run the program.
	* Serialized files are encoded in binary and have the .perhaps filetype.
	*/
	void Serialize(GLMesh* mesh, std::string filepath);

	/*
	* Used for DeSerializing the serialized file.
	*/
	GLMesh* DeSerialize(std::string filepath);

	/*
	* Used for processing the node in assimp's hierarchy.
	*/
	void ProcessNode(GLMesh* glmesh, aiNode* node, const aiScene* scene);

	/*
	* Used for processing the mesh in each node(extracting vertex/uv/normal/etc.)
	*/
	GLMesh* ProcessMesh(GLMesh* glmesh, aiMesh* mesh, const aiScene* scene);

};