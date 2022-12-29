#ifndef MESH_HPP
#define MESH_HPP

#include "../Objects/Eng3D/Cube.hpp"
#include "../Text/Text.hpp"

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
        int AddCube(glm::vec3 pos, float length);


        int AddText(std::string text, glm::vec2 pos, float scale, glm::vec3 color);
        
        
        void UpdateObjectShader(int index, GLuint s);
        void UpdateTextShader(int index, GLuint s);

        void EnableObject(int index);
        void DisableObject(int index);
        int DeleteMesh();

        void Render(bool* keys,struct input::mouse* mouseInfo);

    private:
        void RenderObject(struct object::object& obj);
        void RenderText(text::Text &tex);
        void RenderText(text::Text &tex, std::string& text, float x, float y, float scale, glm::vec3 color);

        GLFWwindow *myWindow = nullptr;

        std::vector<struct object::object> objects;
        std::vector<text::Text> texts;
    };
}


#endif