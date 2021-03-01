#pragma once

#include<glad/glad.h>
#include<cstdint>
#include<string>

#include"NonCopyable.h"

class Texture : public NonCopyable
{
public:
	Texture(const std::string& filename);

	Texture(Texture&& other);
	Texture& operator=(Texture&& rhs);

	~Texture();

	uint32_t getWidth() const { return m_width; }
	uint32_t getHeight() const { return m_height; }

	void bind() const { glBindTexture(GL_TEXTURE_2D, m_id); }
	void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
private:
	void deleteData();
private:
	GLuint m_id = 0;
	uint32_t m_width = 0;
	uint32_t m_height = 0;
};