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

int main()
{
    Window::get();
    Log::get();

    if(!gladLoadGL())
        Log::critical("opengl did not load!");

    Application app;
    app.pushLayer(std::make_unique<GameLayer>());
    app.run();

    return 0;
}