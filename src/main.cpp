#include<iostream>
#include<glm/glm.hpp>

#include<glad/glad.h>

#include<SFML/Graphics.hpp>

#include"util/Log.h"

#include"OpenGL/VertexArray.h"
#include"OpenGL/Shader.h"

#include"Window.h"

#include"Game/Application/Application.h"
#include"Game/GameLayer.h"

/*std::vector<GLfloat> vertices = {
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};
std::vector<GLuint> indices =
{
    0, 1, 3,
    1, 2, 3
};*/

int main()
{
    Window::get();
    Log::get();

    if(!gladLoadGL())
        Log::critical("opengl did not load!");

    Application app;
    app.pushLayer(std::make_unique<GameLayer>());
    app.run();

    /*Shader shader("vertex_shader", "fragment_shader");

    VertexArray vertexArray;
    vertexArray.addAttribute(vertices, 3, "a_position");
    vertexArray.addIndexBuffer(indices);

    vertexArray.showLayout();

    while(Window::isOpen())
    {
        sf::Event event;
        while(Window::pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                Window::close();
        }

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();

        vertexArray.bind();
        glDrawElements(GL_TRIANGLES, vertexArray.getNumberIndices(), GL_UNSIGNED_INT, 0);

        Window::update();
    }*/

    return 0;
}