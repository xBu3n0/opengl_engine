#ifndef CUBE_HPP
#define CUBE_HPP

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Object.hpp"

namespace Eng3D
{
    struct object::object CreateCube(glm::vec3 pos, float length);
}

#endif