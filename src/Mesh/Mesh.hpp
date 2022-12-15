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
    const int FAILURE = 0;
    const int SUCCESS = 1;

    class Mesh
    {
    public:
        Mesh();
        void SetWindow(GLFWwindow* myWindow);

        int AddMesh();
        int AddCube(glm::vec3 pos, float length, shader::Shader s);
        int AddText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);
        int UpdateMesh();
        void EnableObject(int index);
        void DisableObject(int index);
        int DeleteMesh();

        void Render();

    private:
        void RenderObject(struct object::object& obj);
        void RenderText(text::Text &tex, shader::Shader &s);
        // void RenderText(text::Text &tex, shader::Shader &s, std::string& text, float x, float y, float scale, glm::vec3 color);

    private:
        GLFWwindow *myWindow = nullptr;

        std::vector<struct object::object> objects;
        std::vector<text::Text> texts;
    };
}


#endif