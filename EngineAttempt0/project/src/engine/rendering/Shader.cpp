#include "Shader.h"
ShaderProgram* ShaderProgram::activeProgram = nullptr;

Shader::Shader(std::string filepath)
{
	ParseShader(filepath);
}

void Shader::ParseShader(std::string& filepath)
{
	std::ifstream file;
	file.open(filepath);

	if (file.is_open())
	{
		if (filepath.find(".vert") != std::string::npos)
		{
			shaderType = GL_VERTEX_SHADER;
		}
		else if (filepath.find(".frag") != std::string::npos)
		{
			shaderType = GL_FRAGMENT_SHADER;
		}
		else if (filepath.find(".geom") != std::string::npos)
		{
			shaderType = GL_GEOMETRY_SHADER;
		}
		else
		{
			file.close();
			conlog("'" << filepath << "'" <<
				"\n is not a supported shader filetype. it must be of type .vert, .frag or .geom");
			return;
		}

		std::string line;
		std::stringstream sstream;
		while (std::getline(file, line))
		{
			sstream << line << "\n";
		}
		std::string streamstring = sstream.str();

		mID = glCreateShader(shaderType);


		const char* src = streamstring.c_str();
		glShaderSource(mID, 1, &src, 0);
		glCompileShader(mID);

		int result;
		glGetShaderiv(mID, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			int length;
			glGetShaderiv(mID, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)_malloca(length * sizeof(char));
			glGetShaderInfoLog(mID, length, &length, message);
			std::cout << "*** FAILED TO COMPILE SHADER***\n";
			std::string sType = shaderType == GL_VERTEX_SHADER 
				? "Vertex" : shaderType == GL_FRAGMENT_SHADER ? "Fragment" : "Geometry";
			std::cout << "Shader id: " << mID << " of type " << sType << "\n";
			std::cout << message << "\n";
			std::cout << "*******************************";
			delete message;
			glDeleteShader(mID);
		}
	}
	else
	{
		conlog("Could not open shader path");
		conlog("Path: " << filepath);
	}
	file.close();
}

void Shader::Delete()
{
	glDeleteShader(mID);
}


ShaderProgram::ShaderProgram()
{
	mID = glCreateProgram();
}

ShaderProgram::ShaderProgram(Shader& vs, Shader& fs)
{
	mID = glCreateProgram();
	glAttachShader(mID, vs.GetID());
	glAttachShader(mID, fs.GetID());
	LinkProgram();
	Unbind();
}

ShaderProgram::ShaderProgram(std::string vertexFilepath, std::string fragmentFilepath)
{
	Shader vertex(vertexFilepath);
	Shader fragment(fragmentFilepath);

	mID = glCreateProgram();
	RunProgram();
	AttachShader(vertex);
	AttachShader(fragment);
	LinkProgram();

	vertex.Delete();
	fragment.Delete();
	Unbind();
}

void ShaderProgram::LinkProgram()
{
	glLinkProgram(mID);
	glValidateProgram(mID);
}

void ShaderProgram::RunProgram()
{
	if(activeProgram == this)
		return;

	activeProgram = this;
	glUseProgram(mID);
}

void ShaderProgram::AttachShader(Shader& shader)
{
	glAttachShader(mID, shader.GetID());
}

void ShaderProgram::UnbindProgram()
{
	glUseProgram(0);
}

void ShaderProgram::SupressErrors(bool value)
{
	supressed = value;
}

int ShaderProgram::GetUniformLocation(const std::string& name)
{
	if (m_UniformCache.find(name) != m_UniformCache.end())
	{
		return m_UniformCache[name];
	}

	int location = glGetUniformLocation(mID, name.c_str());
	if (location == -1)
	{
		if (!supressed)
			std::cout << "'" << name << "' Uniform doesnt exist\n";
	}
	else
	{
		m_UniformCache[name] = location;
	}

	return location;
}

void ShaderProgram::SetUniform3f(const std::string& name, glm::vec3 vec3)
{
	RunProgram();
	glUniform3f(GetUniformLocation(name), vec3.x, vec3.y, vec3.z);
}

void ShaderProgram::SetMat4f(const std::string& name, const glm::mat4 Matrix4x4)
{
	RunProgram();
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &Matrix4x4[0][0]);
}

void ShaderProgram::SetMat3f(const std::string& name, const glm::mat3 Matrix3x3)
{
	RunProgram();
	glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &Matrix3x3[0][0]);
}

void ShaderProgram::SetUniform4f(const std::string& name, glm::vec4 vec4)
{
	RunProgram();
	glUniform4f(GetUniformLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void ShaderProgram::SetUniform1i(const std::string& name, int value)
{
	RunProgram();
	glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform1f(const std::string& name, float value)
{
	RunProgram();
	glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform2f(const std::string& name, vec2 value)
{
	RunProgram();
	glUniform2f(GetUniformLocation(name), value.x, value.y);
}