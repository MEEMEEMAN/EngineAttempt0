#include "Loader.h"
#include "ModelImporter.h"

RawModel Loader::Load(unsigned int index, unsigned int dimensions, std::vector<float>* positions)
{
	unsigned int vao = GenVAO();
	glBindVertexArray(vao);

	LoadData(index, dimensions, positions);

	unsigned int count = positions->size() / dimensions;
	RawModel model(vao, 0, count);
	return model;
}

RawModel Loader::Load(unsigned int index, std::vector<vec3>* positions)
{
	unsigned int vao = GenVAO();
	glBindVertexArray(vao);

	LoadData(index, positions);

	RawModel model(vao, 0, positions->size() /3);
	return model;
}

RawModel Loader::Load(std::vector<vec3>* positions, std::vector<vec2>* uvs)
{
	unsigned int vao = GenVAO();
	glBindVertexArray(vao);

	LoadData(0, positions);
	LoadData(1, uvs);

	size_t size = positions->size();
	RawModel model(vao, 0, size);
	return model;
}

RawModel Loader::Load(std::vector<vec3>* positions, std::vector<vec2>* uvs, std::vector<unsigned int>* indices)
{
	unsigned int vao = GenVAO();
	glBindVertexArray(vao);

	unsigned int ebo = LoadIndices(indices);
	LoadData(0, positions);
	LoadData(1, uvs);

	size_t size = indices->size();
	RawModel model(vao, ebo, size);
	return model;
}

RawModel Loader::Load(unsigned int index, unsigned int dimensions,
	std::vector<float>* positions, std::vector<unsigned int>* indices)
{
	unsigned int vao = GenVAO();
	glBindVertexArray(vao);

	LoadData(index, dimensions, positions);
	unsigned int ebo = LoadIndices(indices);

	unsigned int count = indices->size();
	RawModel model(vao, ebo, count);
	return model;
}

RawModel Loader::LoadModel(std::vector<vec3>* positions, std::vector<unsigned int>* indices, std::vector<vec2>* uvs, std::vector<vec3>* normals, std::vector<vec3>* tangents, std::vector<vec3>* biTangents)
{
	unsigned int vao = GenVAO();
	glBindVertexArray(vao);
	unsigned int ebo = LoadIndices(indices);
	LoadData(0, positions);
	LoadData(1, uvs);
	LoadData(2, normals);
	LoadData(3, tangents);
	LoadData(4, biTangents);

	unsigned int count = indices->size();
	RawModel model(vao, ebo, count);
	return model;
}

RawModel Loader::ImportSimpleModel(std::string filepath)
{
	GLMesh* glmesh = importer.Import(filepath);

	RawModel model = LoadModel(&glmesh->Positions, &glmesh->indices, 
		&glmesh->UVs, &glmesh->Normals, &glmesh->tangents, &glmesh->biTangents);

	return model;
}


unsigned int Loader::GenVAO()
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	return vao;
}

void Loader::LoadData(unsigned int index, unsigned int dimensions, std::vector<float>* positions)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * positions->size(), &(*positions)[0], GL_STATIC_DRAW);
	glVertexAttribPointer(index, dimensions, GL_FLOAT, false, sizeof(float) * dimensions, 0);
	glEnableVertexAttribArray(index);
}

void Loader::LoadData(unsigned int index, std::vector<vec3>* positions)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * positions->size(), &(*positions)[0], GL_STATIC_DRAW);
	glVertexAttribPointer(index, 3, GL_FLOAT, false, sizeof(vec3), 0);
	glEnableVertexAttribArray(index);

}

void Loader::LoadData(unsigned int index, std::vector<vec2>* positions)
{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vec2) * positions->size(), &(*positions)[0], GL_STATIC_DRAW);
	glVertexAttribPointer(index, 2, GL_FLOAT, false, sizeof(vec2), 0);
	glEnableVertexAttribArray(index);

}

unsigned int Loader::LoadIndices(std::vector<unsigned int>* indices)
{
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * indices->size(), &(*indices)[0], GL_STATIC_DRAW);
	return ebo;
}
