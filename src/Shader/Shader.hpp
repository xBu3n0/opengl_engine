/*

    ERRRO NO SHADER, NÃO ESTÁ FUNCIONANDO.

*/

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <string.h>
#include <fstream>

#include <iostream>

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>

namespace shader
{
    const int FAILURE = 0;
    const int SUCCESS = 1;

    class Shader
    {
    public:
        Shader();

        void CreateFromString(const std::string& vertexCode, const std::string& fragmentCode, GLFWwindow* myWindow);
        void CreateFromFiles(const std::string& vertexLocation, const std::string& fragmentLocation, GLFWwindow* myWindow);

        std::string ReadFile(const std::string& fileLocation);

        // Ver uma forma de pegar inputs de maneira menos estática como está aqui.
        GLuint GetProjectionLocation();
        GLuint GetModelLocation();
        GLuint GetViewLocation();

        // Habilita o Shader para ser utilizado  
        void UseShader();
        // Retira o shader que está sendo utilizado.
        void ClearShader();
        // Recebe o ShaderID para tirar informações sobre o shaders e variaveis que serão utilizadas.
        GLuint GetShaderID();

        // Apagar o shader
        ~Shader();

    private:
        GLuint ShaderID;

        void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);
        void AddShader(GLuint theProgram, const std::string& shaderCode, GLenum shaderType);
    };
}

#endif