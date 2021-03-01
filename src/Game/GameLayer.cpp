#include "GameLayer.h"

#include<vector>
#include<glad/glad.h>

#include"Log.h"


std::vector<GLfloat> vertices = 
{
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

std::vector<GLfloat> texturecoords =
{
    1, 1,
    1, 0,
    0, 0,
    0, 1
};

std::vector<GLuint> indices =
{
    0, 1, 3,
    1, 2, 3
};

GameLayer::GameLayer()
    :m_shader("vertex_shader", "fragment_shader"), m_texture("test.png"), m_quad({0, 0}, {80, 80})
{
}

void GameLayer::onAttach()
{
    m_map.reserve(16 * 9);
    m_va.addAttribute(vertices, 3, "a_position");
    m_va.addAttribute(texturecoords, 2, "a_texcoords");
    m_va.addIndexBuffer(indices);
    m_texture.bind();

    for(int y = 0; y < 9; y++)
    for(int x = 0; x < 16; x++)
    {
        if(y == x)
            continue;
        Quad q({x * 80, y * 80}, {160, 160});
        m_quads.push_back(std::move(q));
    }
}

void GameLayer::onDetach()
{
}

void GameLayer::onUpdate(float dt)
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    m_shader.bind();

    //m_va.bind();
    //glDrawElements(GL_TRIANGLES, m_va.getNumberIndices(), GL_UNSIGNED_INT, 0);
    for(auto& q : m_quads)
        q.draw();
    //m_quad.draw();
}
