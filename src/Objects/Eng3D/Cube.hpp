#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include "../../../glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Eng3D
{
    void CreateCube(std::vector<GLfloat>& data, std::vector<GLuint>& indexes, glm::vec3 pos, float length);
}

#endif