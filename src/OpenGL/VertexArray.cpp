#include "VertexArray.h"

#include"Log.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_id);
}

VertexArray::VertexArray(VertexArray&& other)
    :m_id(other.m_id), m_numberIndices(other.m_numberIndices), m_indexCounter(other.m_indexCounter),
    m_vbos(std::move(other.m_vbos)), m_layout(std::move(other.m_layout))
{
    other.m_id = 0;
    other.m_numberIndices = 0;
    other.m_indexCounter = 0;
    other.m_vbos.clear();
    other.m_layout.clear();
}

VertexArray& VertexArray::operator=(VertexArray&& rhs)
{
    if(this == &rhs)
        return *this;

    deleteData();

    m_id = rhs.m_id;
    m_numberIndices = rhs.m_numberIndices;
    m_indexCounter = rhs.m_indexCounter;
    m_vbos = std::move(rhs.m_vbos);
    m_layout = std::move(rhs.m_layout);

    rhs.m_id = 0;
    rhs.m_numberIndices = 0;
    rhs.m_indexCounter = 0;
    rhs.m_vbos.clear();
    rhs.m_layout.clear();

    return *this;
}

VertexArray::~VertexArray()
{
    deleteData();
}

void VertexArray::addAttribute(const std::vector<GLfloat>& vertexData, uint32_t numDimensions, const std::string& attributeName)
{
    if(vertexData.empty())
    {
        Log::warn("attribute: {} was going to be added but is empty", attributeName);
        return;
    }

    m_layout.push_back({numDimensions, attributeName});

    uint32_t vbo;
    glGenBuffers(1, &vbo);
    glBindVertexArray(m_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData[0]) * vertexData.size(), vertexData.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(m_indexCounter, numDimensions, GL_FLOAT, GL_FALSE, numDimensions * sizeof(vertexData[0]), (void*)0);
    glEnableVertexArrayAttrib(m_id, m_indexCounter++);
    m_vbos.push_back(vbo);
}

void VertexArray::addIndexBuffer(const std::vector<GLuint>& indices)
{
    if(indices.empty())
    {
        Log::warn("index buffer was going to be added but is empty");
        return;
    }

    m_numberIndices = indices.size();

    uint32_t ibo;
    glGenBuffers(1, &ibo);
    glBindVertexArray(m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
    m_vbos.push_back(ibo);
}

void VertexArray::showLayout() const
{
    Log::info("--displaying vertex array layout--");
    Log::info("name:\t\t\t type:");
    for(auto [key, value] : m_layout)
        Log::info("{}\t\t vec{}", value, key);
}

void VertexArray::deleteData()
{
    glDeleteBuffers(m_vbos.size(), m_vbos.data());
    glDeleteVertexArrays(1, &m_id);

    GLuint m_id = 0;
    uint32_t m_indicesCount = 0;
    uint32_t m_indexCounter = 0;
    m_vbos.clear();
    m_layout.clear();
}
