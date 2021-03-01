#include "Quad.h"

#include"../../Window.h"

namespace
{
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
}
#include"Log.h"
Quad::Quad(const glm::vec2& position, const glm::vec2& size)
{
    //the size taken by the quad constructor is in pixels (0, 0) is the top left of the screen
    //opengl's system has the range [-1, 1] for both axis
    //the divisions convert the pixel coords to the device coords
    glm::vec2 devicePos = glm::vec2(position.x / Window::width, 1 - (position.y / Window::height));
    devicePos *= 2;
    devicePos.x -= 1;
    devicePos.y -= 1;

    glm::vec2 deviceSize = glm::vec2(size.x / Window::width, size.y / Window::height);

    std::vector<GLfloat> vertices =
    {
        devicePos.x + deviceSize.x, devicePos.y - deviceSize.y, 0,
        devicePos.x + deviceSize.x, devicePos.y, 0,
        devicePos.x,  devicePos.y, 0,
        devicePos.x,  devicePos.y - deviceSize.y, 0
    };

    m_va.addAttribute(vertices, 3, "a_position");
    m_va.addAttribute(texturecoords, 2, "a_texcoords");
    m_va.addIndexBuffer(indices);
}

void Quad::draw()
{
    m_va.bind();
    glDrawElements(GL_TRIANGLES, m_va.getNumberIndices(), GL_UNSIGNED_INT, 0);
}
