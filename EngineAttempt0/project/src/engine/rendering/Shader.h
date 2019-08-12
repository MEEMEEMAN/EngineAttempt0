#pragma once
#include "pch.h"
#include "GLObject.h"

class Shader : public GLObject
{
	GLuint shaderType;
public:
	Shader(std::string filepath);
	void ParseShader(std::string& filepath);
	inline unsigned int GetType() const
	{
		return shaderType;
	}
	//Delete the shader and free up some memory.
	void Delete();
};

class ShaderProgram : public GLObject
{
public:
	ShaderProgram();

	ShaderProgram(Shader& vs, Shader& fs);

	ShaderProgram(std::string vertexFilepath, std::string fragmentFilepath);

	void LinkProgram();
	void RunProgram();
	void AttachShader(Shader& shader);
	static void UnbindProgram();
	void SupressErrors(bool value);
	bool isActive()
	{
		return activeProgram == this;
	}

	void SetUniform3f(const std::string& name, glm::vec3 vec3);
	void SetMat4f(const std::string& name, const glm::mat4 Matrix4x4);
	void SetMat3f(const std::string& name, const glm::mat3 Matrix3x3);
	void SetUniform4f(const std::string& name, glm::vec4 vec4);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform2f(const std::string& name, vec2 value);

private:
	static ShaderProgram* activeProgram;
	std::unordered_map<std::string, int> m_UniformCache;
	std::vector<std::string> uniformDB;
	int GetUniformLocation(const std::string& name);
	bool supressed = false;
};