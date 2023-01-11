/*

    ERRRO NO SHADER, NÃO ESTÁ FUNCIONANDO.

*/

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <string.h>
#include <fstream>

#include <map>
#include <vector>
#include <iostream>

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#include <windows.h>
#endif
#include "../../glad/glad.h"
#include <GLFW/glfw3.h>

namespace shader
{
    const int FAILURE = 0;
    const int SUCCESS = 1;
    
    struct inInfo
    {
        std::string varType;
        GLuint inValue = 0;

        bool operator==(const struct inInfo& b)
        {
            return this->varType == b.varType;
        }
        bool operator!=(const struct inInfo& b)
        {
            return !(*this == b);
        }
    };
    struct uniformInfo
    {
        std::string varType;
        GLuint inValue = 0;
        
        bool operator==(struct uniformInfo& b)
        {
            return this->varType == b.varType;
        }
        bool operator!=(struct uniformInfo& b)
        {
            return !(*this == b);
        }
    };
    struct layoutInfo
    {
        std::string location;
        std::string varType;
        std::string type;
        GLuint inValue = 0;

        bool operator==(struct layoutInfo& b)
        {
            return (this->location == b.location) && (this->varType == b.varType) && (this->type == b.type);
        }
        bool operator!=(struct layoutInfo& b)
        {
            return !(*this == b);
        }
    };

    class Shader
    {
    public:
        Shader();

        void CreateFromString(const std::string& vertexCode, const std::string& fragmentCode, GLFWwindow* myWindow);
        void CreateFromFiles(const std::string& vertexLocation, const std::string& fragmentLocation, GLFWwindow* myWindow);

        std::string ReadFile(const std::string& fileLocation);
        std::vector<std::string> SplitString(const std::string& str);
        void MapVariables(const std::string& str);

        // Ver uma forma de pegar inputs de maneira menos estática como está aqui.
        std::map<std::string, struct inInfo     > in;
        std::map<std::string, struct uniformInfo> uniform;
        std::map<std::string, struct layoutInfo > layout;

        // Habilita o Shader para ser utilizado  
        void UseShader();
        // Retira o shader que está sendo utilizado.
        void ClearShader();
        // Recebe o ShaderID para tirar informações sobre o shaders e variaveis que serão utilizadas.
        GLuint GetShaderID();

        // Apagar o shader
        ~Shader();

    private:
        GLuint ShaderID = 0;

        void CompileShader(const std::string& vertexCode, const std::string& fragmentCode);
        void AddShader(GLuint theProgram, const std::string& shaderCode, GLenum shaderType);
    };
}

#endif