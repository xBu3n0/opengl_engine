#ifndef MESH_HPP
#define MESH_HPP

#include "../Shader/Shader.hpp"
#include "../Text/Text.hpp"
#include "../Objects/Eng3D/Cube.hpp"

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <cstdlib>


namespace mesh
{
    struct object
    {
        GLuint VAO;

        GLuint VBO;
        GLuint verticesCount;
        
        GLuint IBO;
        bool useIBO;
        GLuint indexCount;
        
        bool willBeRendered;
        GLuint typeOfRendering;

        std::vector<GLfloat> data;
    };

    const int FAILURE = 0;
    const int SUCCESS = 1;

    class Mesh
    {
    public:
        Mesh();
    
        int AddMesh();
        int AddCube(glm::vec3 pos, float length);
        int AddText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);
        int UpdateMesh();
        void EnableObject(int index);
        void DisableObject(int index);
        int DeleteMesh();

        void Render();

        void RenderMesh();

        int shaderID;

    private:
        shader::Shader s;
        
        void RenderObject(struct object& obj);
        void RenderText(text::Text &tex, shader::Shader &s);
        // void RenderText(text::Text &tex, shader::Shader &s, std::string& text, float x, float y, float scale, glm::vec3 color);

        std::vector<struct object> objects;
        std::vector<text::Text> texts;
    };
}


#endif