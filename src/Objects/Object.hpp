#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

#include "../Shader/Shader.hpp"
#include "../../glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace object
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
        GLuint s;

        void (*HowToRender)(struct object& obj);
    };
}

#endif