#version 330

in vec3 p;
out vec4 colour;

void main()
{
	colour = vec4(p, 1.0f);
}