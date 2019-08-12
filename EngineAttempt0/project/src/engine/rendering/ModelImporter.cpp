#include "ModelImporter.h"

GLMesh* ModelImporter::Import(std::string filepath)
{
	std::string queryFile;
	{
		size_t last = filepath.find_last_of('/');
		std::string directory = filepath.substr(0, last) + "/";
		std::string filename = filepath.substr(last + 1, filepath.size());
		size_t pathLess = filename.find_last_of(".");
		std::string fileTypeless = filename.substr(0, pathLess);
		queryFile = directory + fileTypeless + ".perhaps";
	}

	bool exists = true;
	if (fileExists(queryFile))
	{
		conlog(queryFile << " was found. using that instead.");
		GLMesh* model = DeSerialize(queryFile);
		return model;
	}
	else
	{
		exists = false;
	}


	conlog("*** BEGINNING MODEL IMPORT***");
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filepath, aiProcess_JoinIdenticalVertices
		| aiProcess_Triangulate | aiProcess_CalcTangentSpace);

	std::string error = importer.GetErrorString();

	if (error.length() > 1)
	{
		conlog(error);
		__debugbreak();
	}
	aiNode* root = scene->mRootNode;

	GLMesh* glmesh = new GLMesh();
	totalVertexCount = 0;
	ProcessNode(glmesh, root, scene);

	if (!exists)
	{
		Serialize(glmesh, queryFile);
	};

	return glmesh;
}

void ModelImporter::Serialize(GLMesh* mesh, std::string filepath)
{
	std::fstream stream(filepath, std::ios::out | std::ios::binary | std::ios::trunc);

	size_t posSize = mesh->Positions.size();
	size_t uvSize = mesh->UVs.size();
	size_t normalSize = mesh->Normals.size();
	size_t indiSize = mesh->indices.size();
	size_t tangSize = mesh->tangents.size();
	size_t biTangSize = mesh->biTangents.size();


	stream.write((char*)& posSize, sizeof(size_t));
	stream.write((char*)& uvSize, sizeof(size_t));
	stream.write((char*)& normalSize, sizeof(size_t));
	stream.write((char*)& indiSize, sizeof(size_t));

	stream.write((char*)& tangSize, sizeof(size_t));
	stream.write((char*)& biTangSize, sizeof(size_t));


	for (size_t i = 0; i < posSize; i++)
		stream.write((char*)& mesh->Positions[i], sizeof(vec3));

	for (size_t i = 0; i < uvSize; i++)
		stream.write((char*)& mesh->UVs[i], sizeof(vec2));

	for (size_t i = 0; i < normalSize; i++)
		stream.write((char*)& mesh->Normals[i], sizeof(vec3));

	for (size_t i = 0; i < indiSize; i++)
		stream.write((char*)& mesh->indices[i], sizeof(unsigned int));

	for (size_t i = 0; i < tangSize; i++)
		stream.write((char*)& mesh->tangents[i], sizeof(vec3));

	for (size_t i = 0; i < biTangSize; i++)
		stream.write((char*)& mesh->biTangents[i], sizeof(vec3));


	stream.close();
}

GLMesh* ModelImporter::DeSerialize(std::string filepath)
{
	GLMesh mesh;
	std::fstream stream(filepath, std::ios::in | std::ios::binary);

	size_t posSize;
	size_t uvSize;
	size_t normalSize;
	size_t indiSize;
	size_t tangSize;
	size_t biTangSize;


	stream.read((char*)& posSize, sizeof(size_t));
	stream.read((char*)& uvSize, sizeof(size_t));
	stream.read((char*)& normalSize, sizeof(size_t));
	stream.read((char*)& indiSize, sizeof(size_t));

	stream.read((char*)& tangSize, sizeof(size_t));
	stream.read((char*)& biTangSize, sizeof(size_t));

	for (size_t i = 0; i < posSize; i++)
	{
		vec3 vector;
		stream.read((char*)& vector[0], sizeof(vec3));
		mesh.Positions.push_back(vector);
	}

	for (size_t i = 0; i < uvSize; i++)
	{
		vec2 vector;
		stream.read((char*)& vector[0], sizeof(vec2));
		mesh.UVs.push_back(vector);
	}

	for (size_t i = 0; i < normalSize; i++)
	{
		vec3 vector;
		stream.read((char*)& vector[0], sizeof(vec3));
		mesh.Normals.push_back(vector);
	}

	for (size_t i = 0; i < indiSize; i++)
	{
		unsigned int index;
		stream.read((char*)& index, sizeof(unsigned int));
		mesh.indices.push_back(index);
	}

	for (size_t i = 0; i < tangSize; i++)
	{
		vec3 vector;
		stream.read((char*)& vector, sizeof(vec3));
		mesh.tangents.push_back(vector);
	}

	for (size_t i = 0; i < biTangSize; i++)
	{
		vec3 vector;
		stream.read((char*)& vector, sizeof(vec3));
		mesh.biTangents.push_back(vector);
	}

	stream.close();

	GLMesh* glmesh = new GLMesh();
	glmesh->Positions = mesh.Positions;
	glmesh->indices = mesh.indices;
	glmesh->UVs = mesh.UVs;
	glmesh->Normals = mesh.Normals;
	glmesh->tangents = mesh.tangents;
	glmesh->biTangents = mesh.biTangents;

	return  glmesh;
}

void ModelImporter::ProcessNode(GLMesh* glmesh, aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(glmesh, node->mChildren[i], scene);
	}

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(glmesh, mesh, scene);
	}

	return;
}

GLMesh* ModelImporter::ProcessMesh(GLMesh* glmesh, aiMesh* mesh, const aiScene* scene)
{
	totalVertexCount += mesh->mNumVertices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vec3 vertex;
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;

		glmesh->Positions.push_back(vertex);

		vertex.x = mesh->mNormals[i].x;
		vertex.y = mesh->mNormals[i].y;
		vertex.z = mesh->mNormals[i].z;
		glmesh->Normals.push_back(vertex);

		if (mesh->mTextureCoords[0]) //Currently we only support 1 set of tex coords.
		{
			vec2 uv;
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
			glmesh->UVs.push_back(uv);
		}
		else
		{
			glmesh->UVs.push_back(vec2(0));
		}

		vertex.x = mesh->mTangents[i].x;
		vertex.y = mesh->mTangents[i].y;
		vertex.z = mesh->mTangents[i].z;
		glmesh->tangents.push_back(vertex);

		vertex.x = mesh->mBitangents[i].x;
		vertex.y = mesh->mBitangents[i].y;
		vertex.z = mesh->mBitangents[i].z;
		glmesh->biTangents.push_back(vertex);
	}


	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			glmesh->indices.push_back(face.mIndices[j]);
		}
	}

	return glmesh;
}

bool ModelImporter::fileExists(std::string file)
{
	std::fstream query(file);
	return query.good();
}