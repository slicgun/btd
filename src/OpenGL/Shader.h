#pragma once

#include<string>
#include<unordered_map>

#include<glad/glad.h>
#include<glm/matrix.hpp>

#include"NonCopyable.h"
#include"Log.h"

class Shader : public NonCopyable
{
public:
	Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	Shader(Shader&& other);
	Shader& operator=(Shader&& rhs);

	~Shader();

	void bind() const { glUseProgram(m_id); }

	void loadUniformMatrix(const std::string& name, const glm::mat4& matrix);

	template<typename... Ts>
	void loadUniform(const std::string& name, Ts&&... args)
	{
		if(typeid(std::common_type<Ts...>) == typeid(int))
		{
			if constexpr(sizeof...(Ts) == 1)
				glUniform1i(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 2)
				glUniform2i(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 3)
				glUniform3i(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 4)
				glUniform4i(getUniformLocation(name), std::forward<Ts>(args)...);
		}

		else if(typeid(std::common_type<Ts...>) == typeid(float))
		{
			if constexpr(sizeof...(Ts) == 1)
				glUniform1f(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 2)
				glUniform2f(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 3)
				glUniform3f(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 4)
				glUniform4f(getUniformLocation(name), std::forward<Ts>(args)...);
		}

		if(typeid(std::common_type<Ts...>) == typeid(uint32_t))
		{
			if constexpr(sizeof...(Ts) == 1)
				glUniform1ui(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 2)
				glUniform2ui(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 3)
				glUniform3ui(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 4)
				glUniform4ui(getUniformLocation(name), std::forward<Ts>(args)...);
		}

		if(typeid(std::common_type<Ts...>) == typeid(bool))
		{
			if constexpr(sizeof...(Ts) == 1)
				glUniform1i(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 2)
				glUniform2i(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 3)
				glUniform3i(getUniformLocation(name), std::forward<Ts>(args)...);
			if constexpr(sizeof...(Ts) == 4)
				glUniform4i(getUniformLocation(name), std::forward<Ts>(args)...);
		}

		else
		{
			Log::warn("could not determine uniform: {}", name);
		}
	}
private:
	void deleteData();
	GLint getUniformLocation(const std::string& name);

	std::string getShaderSrc(const std::string& filename);
	GLuint compileShader(const char* src, GLenum shaderType);
	void linkProgram(GLuint vertexShader, GLuint fragmentShader);
private:
	GLuint m_id;
	std::unordered_map<std::string, GLint> m_uniformLocations;
};