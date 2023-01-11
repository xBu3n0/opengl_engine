/*

    ERRRO NO SHADER, NÃO ESTÁ FUNCIONANDO.

*/

#include "Shader.hpp"

namespace shader
{
    Shader::Shader()
    {
        ShaderID = 0;
    }

    void Shader::CreateFromString(const std::string& vertexCode, const std::string& fragmentCode, GLFWwindow* myWindow)
    {
        glfwMakeContextCurrent(myWindow);
        CompileShader(vertexCode, fragmentCode);

        MapVariables(vertexCode);
    }

    std::vector<std::string> Shader::SplitString(const std::string& str)
    {
        std::vector<std::string> out;
        std::string aux = "";

        for (char c : str)
            if ((c == ' ' || c == '\n') && !aux.empty())
                out.push_back(aux), aux.clear();
            else if(c != ' ' && c != '\n')
                aux.push_back(c);
        
        if (aux.size() > 0)
            out.push_back(aux), aux.clear();

        return out;
    }

    void Shader::MapVariables(const std::string& str)
    {
        std::vector<std::string> out = SplitString(str);

        unsigned long long i = 0;

        while (i < out.size() && out[i] != "//InicioDaLeitura")
            ++i;


        for (; i < out.size() && out[i] != "//FimDaLeitura"; ++i)
        {
            if (out[i] == "in")
            {
                if (out.size() <= i + 2)
                { std::cout << "Erro na leitura do arquivo" << std::endl; break; }

                out.at(i + 2).pop_back();

                struct inInfo newIn = {
                    out.at(i + 1),
                    glGetUniformLocation(ShaderID, out.at(i+2).data())
                };

                in[out.at(i + 2)] = newIn;

                i += 2;
                continue;
            }
            if (out[i] == "uniform")
            {
                if (out.size() <= i + 2)
                { std::cout << "Erro na leitura do arquivo" << std::endl; break; }

                out.at(i + 2).pop_back();

                std::cout << "glGetUniform(" << out.at(i + 2).data() << ") usando o ShaderID " << ShaderID << ": " << glGetUniformLocation(ShaderID, out.at(i+2).data()) << std::endl;

                struct uniformInfo newUniform = {
                    out.at(i + 1),
                    glGetUniformLocation(ShaderID, out.at(i + 2).data())
                };

                uniform[out.at(i + 2)] = newUniform;

                i += 2;
                continue;
            }
            if (out[i] == "layout")
            {
                if (out.size() <= i + 4)
                { std::cout << "Erro na leitura do arquivo" << std::endl; break; }

                out.at(i + 4).pop_back();

                struct layoutInfo newLayout = {
                    out.at(i + 1),
                    out.at(i + 3),
                    out.at(i + 2),
                    0
                    // glGetUniformLocation(ShaderID, out.at(i + 4).data())
                };

                layout[out.at(i + 4)] = newLayout;

                i += 4;
                continue;
            }
        }
    }

    void Shader::CreateFromFiles(const std::string& vertexLocation, const std::string& fragmentLocation, GLFWwindow* myWindow)
    {// Cria com base nos arquivos que foram informados.
        glfwMakeContextCurrent(myWindow);
        std::string vertexString = ReadFile(vertexLocation);
        std::string fragmentString = ReadFile(fragmentLocation);


        std::string vertexCode = vertexString.c_str();
        std::string fragmentCode = fragmentString.c_str();

        CompileShader(vertexCode, fragmentCode);

        MapVariables(vertexCode);

        std::cout << "Variaveis uniform do shader: " << std::endl;
        for (auto x : uniform)
            std::cout << '\t' << x.second.varType << std::endl;

        std::cout << "Variaveis layout do shader: " << std::endl;
        for (auto x : layout)
            std::cout << '\t' << x.second.location << " " << x.second.varType << " " << x.second.type << std::endl;
    }

    std::string Shader::ReadFile(const std::string& fileLocation)
    {
        std::string content;
        std::ifstream fileStream(fileLocation, std::ios::in);

        if(!fileStream.is_open())
        {
            std::cout << "Failed to read " << fileLocation << "! File doesn't exist." << std::endl;
            return "";
        }

        std::string line = "";

        while(!fileStream.eof())
        {
            std::getline(fileStream, line);
            content.append(line + "\n");
        }

        fileStream.close();
        return content;
    }

    void Shader::CompileShader(const std::string& vertexCode, const std::string& fragmentCode)
    {
        ShaderID = glCreateProgram();

        if(!ShaderID)
        {
            printf("Error creating shader program!\n");
            return;
        }

        AddShader(ShaderID, vertexCode, GL_VERTEX_SHADER);
        AddShader(ShaderID, fragmentCode, GL_FRAGMENT_SHADER);

        GLint result = 0;
        GLchar eLog[1024] = { 0 };

        glLinkProgram(ShaderID);
        glGetProgramiv(ShaderID, GL_LINK_STATUS, &result);
        if(!result)
        {
            glGetProgramInfoLog(ShaderID, sizeof(eLog), NULL, eLog);
            printf("Error linking program: '%s'\n", eLog);
            return;
        }

        glValidateProgram(ShaderID);
        glGetProgramiv(ShaderID, GL_VALIDATE_STATUS, &result);
        if(!result)
        {
            glGetProgramInfoLog(ShaderID, sizeof(eLog), NULL, eLog);
            printf("Error validating program: '%s'\n", eLog);
            return;
        }
    }

    GLuint Shader::GetShaderID()
    {
        return ShaderID;
    }

    void Shader::UseShader()
    {
        glUseProgram(ShaderID);
    }

    void Shader::ClearShader()
    {
        if(ShaderID != 0)
        {
            glDeleteProgram(ShaderID);
            ShaderID = 0;
        }
    }


    void Shader::AddShader(GLuint theProgram, const std::string& shaderCode, GLenum shaderType)
    {
        GLuint theShader = glCreateShader(shaderType);

        const GLchar* theCode[1] = {};
        theCode[0] = shaderCode.data();

        GLint codeLength[1] = {};
        codeLength[0] = static_cast<GLint>(shaderCode.size());

        glShaderSource(theShader, 1, theCode, codeLength);
        glCompileShader(theShader);

        GLint result = 0;
        GLchar eLog[1024] = { 0 };

        glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
        if(!result)
        {
            glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
            printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
            return;
        }

        glAttachShader(theProgram, theShader);
    }

    Shader::~Shader()
    {
        ClearShader();
    }
}