#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

#include "../Shader/Shader.hpp"
#include "../Camera/Camera.hpp"
#include "../Input/Input.hpp"

#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#include <windows.h>
#endif
#include "../../glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace object
{
    struct object
    {
        GLuint VAO = 0;

        GLuint VBO = 0;
        GLuint verticesCount = 0;
        
        GLuint IBO = 0;
        bool useIBO = false;
        GLuint indexCount = 0;
        
        bool willBeRendered = false;
        GLuint typeOfRendering = 0;

        std::vector<GLfloat> data;
        shader::Shader *shader;
        // GLuint shaderID;

        std::map<std::string, struct shader::inInfo     > RequireIn;
        std::map<std::string, struct shader::uniformInfo> RequireUniform;
        std::map<std::string, struct shader::layoutInfo > RequireLayout;

        void (*HowToRender)(struct object& obj, bool* keys, struct input::mouse* mouseInfo, camera::Camera* camera) = nullptr;
    };
}

#endif