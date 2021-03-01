#include "Texture.h"

#include"Log.h"
#include<SFML/Graphics/Image.hpp>

Texture::Texture(const std::string& filename)
{
	sf::Image data;
	bool success = data.loadFromFile("res/textures/" + filename);
	data.flipVertically();

	if(!success)
	{
		Log::critical("failed to load texture: res/textures/{}", filename);
		return;
	}

	m_width = data.getSize().x;
	m_height = data.getSize().y;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.getPixelsPtr());
}

Texture::Texture(Texture&& other)
	:m_id(other.m_id), m_width(other.m_width), m_height(other.m_height)
{
	other.m_id = 0;
	other.m_width = 0;
	other.m_height = 0;
}

Texture& Texture::operator=(Texture&& rhs)
{
	if(this == &rhs)
		return *this;

	deleteData();

	m_id = rhs.m_id;
	m_width = rhs.m_width;
	m_height = rhs.m_height;

	rhs.m_id = 0;
	rhs.m_width = 0;
	rhs.m_height = 0;

	return *this;
}

Texture::~Texture()
{
	deleteData();
}

void Texture::deleteData()
{
	glDeleteTextures(1, &m_id);
	m_id = 0;
	m_width = 0;
	m_height = 0;
}
