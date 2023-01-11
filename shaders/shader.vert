#version 330

//InicioDaLeitura

layout (location=0) in vec3 pos;
out vec3 p;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

//FimDaLeitura

void main()
{
    p = vec3((1+pos.x)/2.0, (1+pos.y)/2.0, (1+pos.z)/8.0);
    gl_Position = projection * view * model * vec4(pos, 1.0);
}