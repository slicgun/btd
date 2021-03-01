#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoords;

out vec2 v_texcoords;

void main()
{
   gl_Position = vec4(a_position.xyz, 1.0);
   v_texcoords = a_texcoords;
}
