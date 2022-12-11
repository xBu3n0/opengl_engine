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

        void CreateFromString(const char* vertexCode, const char* fragmentCode);
        void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

        std::string ReadFile(const char* fileLocation);

        // Ver uma forma de pegar inputs de maneira menos estática como está aqui.
        GLuint GetProjectionLocation();
        GLuint GetModelLocation();
        GLuint GetViewLocation();

        // Habilita o Shader para ser utilizado  
        void UseShader();
        // Retira o shader que está sendo utilizado.
        void ClearShader();

        GLuint GetShaderID();

        // Apagar o shader
        ~Shader();

    private:
        GLuint ShaderID;

        void CompileShader(const char* vertexCode, const char* fragmentCode);
        void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    };
}


/*
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
    class Shader
    {
        public:
            Shader();

            // Cria o `Program` para ser utilizado quando for realizado o desenho. 
            void CreateFromString(const char* vertexCode, const char* fragmentCode);
            void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

            std::string ReadFile(const char* fileLocation);

            GLuint GetProjectionLocation();
            GLuint GetModelLocation();
            GLuint GetViewLocation();

            void UseShader();
            void ClearShader();

            ~Shader();

        private:
            GLuint shaderID, uniformProjection, uniformModel, uniformView;

            void CompileShader(const char* vertexCode, const char* fragmentCode);
            void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    };
}

#endif
*/

#endif