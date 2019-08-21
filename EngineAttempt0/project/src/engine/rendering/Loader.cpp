#include "Loader.h"
#include "ModelImporter.h"

AudioMaster* Loader::audioMaster = nullptr;

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

GLCube Loader::LoadCubemap(std::string directory)
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

GLTexture Loader::loadTexture(std::string filepath, bool flipVertically)
{
	unsigned int id;
	Image image(filepath, flipVertically);

	GLuint format = GL_RGB;
	switch (image.PixelChannels())
	{
	case 3:
		format = GL_RGB;
		break;
	case 4:
		format = GL_RGBA;
		break;
	default:
		conlog("UnSupported image format? " << image.PixelChannels() << " channels found.");
		return	GLTexture(0);
	}

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.4f);

	glTexImage2D(GL_TEXTURE_2D, 0, format, image.GetImageWidth(), image.GetImageHeight(), 0,
		format, GL_UNSIGNED_BYTE, image.GetImageData());

	glGenerateMipmap(GL_TEXTURE_2D);

	return GLTexture(id);
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
