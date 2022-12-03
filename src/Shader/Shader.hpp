#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <string.h>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace shader
{
    const int FAILURE = 0;
    const int SUCCESS = 1;

    class Shader
    {
    public:
        Shader();

        // Cria o `Program` para ser utilizado quando for realizado o desenho. 
        int CreateFromString(const char* vertexCode, const char* fragmentCode);
        int CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
        
        // Lê o arquivo.
        std::string ReadFile(const char* fileLocation);

        // Ver uma forma de pegar inputs de maneira menos estática como está aqui.
        GLuint GetProjectionLocation();
        GLuint GetModelLocation();
        GLuint GetViewLocation();

        // Habilita o Shader para ser utilizado  
        void UseShader();
        // Retira o shader que está sendo utilizado.
        void ClearShader();

        // Apagar o shader
        ~Shader();

    private:
        // Ver uma forma de pegar inputs de maneira menos estática como está aqui.
        GLuint shaderID, uniformProjection, uniformModel, uniformView;

        //
        int CompileShader(const char* vertexCode, const char* fragmentCode);
        //
        int AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
    };
}

#endif