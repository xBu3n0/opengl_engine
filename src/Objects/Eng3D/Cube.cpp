#include "Cube.hpp"

namespace Eng3D
{
    void CreateCube(std::vector<GLfloat>& data, std::vector<GLuint>& indexes, glm::vec3 pos, float length)
    {
        data = {
            pos.x,          pos.y,          pos.z,
            pos.x+length,   pos.y,          pos.z,
            pos.x+length,   pos.y+length,   pos.z,
            pos.x+length,   pos.y,          pos.z+length,
            pos.x,          pos.y+length,   pos.z,
            pos.x,          pos.y+length,   pos.z+length,
            pos.x,          pos.y,          pos.z+length,
            pos.x+length,   pos.y+length,   pos.z+length
        };

        indexes = {
            0, 2, 1,
            0, 2, 4,
            0, 3, 1,
            0, 3, 6,
            0, 5, 4,
            0, 5, 6,
            7, 1, 2,
            7, 1, 3,
            7, 6, 3,
            7, 6, 5,
            7, 4, 2,
            7, 4, 5
        };
    }
}