#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Object.hpp"

namespace Eng2D
{
    struct object::object CreateTriangle(std::vector<GLfloat>& data);
}

#endif