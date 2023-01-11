#version 330

//InicioDaLeitura

layout (location=0) in vec3 pos;
out vec3 p;

//FimDaLeitura

void main()
{
    p = vec3((1+pos.x)/2.0, (1+pos.y)/2.0, (1+pos.z)/8.0);
    gl_Position = vec4(pos, 1.0);
}