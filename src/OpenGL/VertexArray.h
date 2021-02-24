#pragma once

#include<glad/glad.h>

#include<vector>
#include<string>

#include"NonCopyable.h"

class VertexArray : public NonCopyable
{
public:
	VertexArray();
	VertexArray(VertexArray&& other);
	VertexArray& operator=(VertexArray&& rhs);

	~VertexArray();

	///vertex array modification
	void addAttribute(const std::vector<GLfloat>& vertexData, uint32_t numDimensions, const std::string& attributeName = "");
	void addIndexBuffer(const std::vector<GLuint>& indices);


	///utility function
	void bind() const { glBindVertexArray(m_id); }
	void unbind() const { glBindVertexArray(0); }
	void showLayout() const;
	uint32_t getNumberIndices() const { return m_numberIndices; }
private:
	void deleteData();
private:
	GLuint m_id = 0;
	uint32_t m_numberIndices = 0;
	uint32_t m_indexCounter = 0;

	std::vector<GLuint> m_vbos;
	std::vector<std::pair<int, std::string>> m_layout;
};