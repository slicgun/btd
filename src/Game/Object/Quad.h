#pragma once

#include"../OpenGL/VertexArray.h"
#include<glm/vec2.hpp>

class Quad
{
public:
	Quad(const glm::vec2& position, const glm::vec2& size);

	void draw();
private:
	VertexArray m_va;
};