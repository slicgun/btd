#include "Shader.h"

#include<fstream>
#include<sstream>

#include<glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
	:m_id(glCreateProgram())
{
	auto vertexShaderSrc = getShaderSrc("res/shaders/" + vertexShaderFile + ".glsl");
	auto fragmentShaderSrc = getShaderSrc("res/shaders/" + fragmentShaderFile + ".glsl");

	auto vertexShader = compileShader(vertexShaderSrc.c_str(), GL_VERTEX_SHADER);
	auto fragmentShader = compileShader(fragmentShaderSrc.c_str(), GL_FRAGMENT_SHADER);

	linkProgram(vertexShader, fragmentShader);
}

Shader::Shader(Shader&& other)
	:m_id(other.m_id), m_uniformLocations(std::move(other.m_uniformLocations))
{
	other.m_id = 0;
	other.m_uniformLocations.clear();
}

Shader& Shader::operator=(Shader&& rhs)
{
	if(this == &rhs)
		return *this;

	deleteData();

	m_id = rhs.m_id;
	m_uniformLocations = std::move(rhs.m_uniformLocations);

	rhs.m_id = 0;
	rhs.m_uniformLocations.clear();

	return *this;
}

Shader::~Shader()
{
	deleteData();
}

void Shader::loadUniformMatrix(const std::string& name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::deleteData()
{
	glDeleteProgram(m_id);
	m_uniformLocations.clear();
	m_id = 0;
}

GLint Shader::getUniformLocation(const std::string& name)
{
	if(m_uniformLocations.find(name) != m_uniformLocations.end())
		return m_uniformLocations[name];

	GLint location = glGetUniformLocation(m_id, name.c_str());
	m_uniformLocations[name] = location;
	if(location < 0)
		Log::warn("uniform: {}, is invalid or unused", name);
	
	return location;
}

std::string Shader::getShaderSrc(const std::string& filename)
{
	std::fstream file;
	file.open(filename);
	if(!file.is_open())
		Log::critical("failed to load shader source file: {}", filename);
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

GLuint Shader::compileShader(const char* src, GLenum shaderType)
{
	auto shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		Log::critical("failed to compile shader, output: {}", infoLog);
	}
	return shader;
}

void Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader)
{
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	int success;
	char infoLog[512];
	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if(!success) {
		glGetProgramInfoLog(m_id, 512, NULL, infoLog);
		Log::critical("failed to link shaders, output: {}", infoLog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
