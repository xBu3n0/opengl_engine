#include "Cube.hpp"

namespace Eng3D
{
    struct object::object CreateCube(glm::vec3 pos, float length)
    {
        GLuint VAO, VBO;

        /*
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
        */

        std::vector<GLfloat> data = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        };

        std::vector<GLuint> vertices;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        object::object obj = {
            VAO,
            VBO,
            (GLuint) data.size(),
            0,
            false,
            (GLuint) vertices.size(),
            true,
            GL_TRIANGLES,
            data,
            0
        };

        return obj;
    }
}