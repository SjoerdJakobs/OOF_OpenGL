#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"

Shader::Shader(const std::string& filePath) : m_FilePath(filePath), m_RenderID(0)
{
	ShaderProgramSource source = ParseShader(filePath);
	m_RenderID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GL_CALL(glDeleteProgram);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[static_cast<int>(type)] << line << '\n';
		}
	}

	return{ ss[0].str() , ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	GL_CALL(glShaderSource(id, 1, &src, nullptr));
	GL_CALL(glCompileShader(id));

	int result;
	GL_CALL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int length;
		GL_CALL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)_malloca(length * sizeof(char));
		GL_CALL(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		std::cout << message << std::endl;
		GL_CALL(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GL_CALL(glAttachShader(program, vs));
	GL_CALL(glAttachShader(program, fs));
	GL_CALL(glLinkProgram(program));
	GL_CALL(glValidateProgram(program));

	GL_CALL(glDeleteShader(vs));
	GL_CALL(glDeleteShader(fs));

	return program;
}

void Shader::Bind() const
{
	GL_CALL(glUseProgram(m_RenderID));
}

void Shader::UnBind() const
{
	GL_CALL(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GL_CALL(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GL_CALL(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
	GL_CALL(glUniform2f(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GL_CALL(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GL_CALL(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GL_CALL(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	GL_CALL(int location = glGetUniformLocation(m_RenderID, name.c_str()));
	if (location == -1)
	{
		std::cout << "warning: uniform '" << name << "' doesn't exist";
	}

	m_UniformLocationCache[name] = location;
	return location;
}