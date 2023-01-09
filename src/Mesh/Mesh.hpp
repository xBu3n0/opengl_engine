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

        int AddCube(glm::vec3 pos, float length, std::string object_name);


        int AddText(std::string text, glm::vec2 pos, float scale, glm::vec3 color, std::string name);
        
        
        int UpdateObjectShader(const char* name, GLuint s);

        int UpdateTextData(const char* name, const char* text);
        int UpdateTextShader(const char* name, GLuint s);

        int EnableObject(const char* name);
        int DisableObject(const char* name);
        int DeleteMesh(const char* name);

        void Render(bool* keys,struct input::mouse* mouseInfo);

    public:
        std::map<std::string, struct object::object> objects;
        std::map<std::string, text::Text> texts;

    private:
        void RenderObject(struct object::object& obj);
        void RenderText(text::Text &tex);
        // void RenderText(text::Text &tex, std::string& text, float x, float y, float scale, glm::vec3 color);

        GLFWwindow* myWindow = nullptr;
    };
}


#endif