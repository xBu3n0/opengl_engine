#version 330
layout (location = 0) in vec3 pos;

void main()
{
    gl_Position = vec4(pos.x, pos.y * 0.4, pos.z, 1.0);
}