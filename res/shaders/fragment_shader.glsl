#version 460 core

uniform sampler2D tex;

out vec4 outColor;

in vec2 v_texcoords;

void main()
{
   outColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   outColor = texture(tex, v_texcoords);
}
