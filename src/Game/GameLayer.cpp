#include "GameLayer.h"

#include<vector>
#include<glad/glad.h>

#include"Log.h"

std::vector<GLfloat> vertices = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
std::vector<GLuint> indices =
{
    0, 1, 3,
    1, 2, 3
};

GameLayer::GameLayer()
    :m_shader("vertex_shader", "fragment_shader")
{
}

void GameLayer::onAttach()
{
    Log::info("dasd");
    m_va.addAttribute(vertices, 3, "a_position");
    m_va.addIndexBuffer(indices);
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(float dt)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader.bind();

    m_va.bind();
    glDrawElements(GL_TRIANGLES, m_va.getNumberIndices(), GL_UNSIGNED_INT, 0);
}
