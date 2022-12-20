#include "Cube.hpp"

namespace Eng3D
{
    void HowToRender(struct object::object &obj)
    {
        glUseProgram(obj.s);

        glBindVertexArray(obj.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, obj.VBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.IBO);
        glDrawElements(obj.typeOfRendering, obj.indexCount, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        glUseProgram(0);

        return;
    }

    struct object::object CreateCube(glm::vec3 pos, float length)
    {
        GLuint VAO, VBO, IBO;

        std::vector<GLfloat> data = {
            pos.x,          pos.y,          pos.z,
            pos.x+length,   pos.y,          pos.z,
            pos.x+length,   pos.y+length,   pos.z,
            pos.x+length,   pos.y,          pos.z+length,
            pos.x,          pos.y+length,   pos.z,
            pos.x,          pos.y+length,   pos.z+length,
            pos.x,          pos.y,          pos.z+length,
            pos.x+length,   pos.y+length,   pos.z+length
        };

        std::vector<uint> indexes = {
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

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(0);


        object::object obj = {
            VAO,
            VBO,
            (GLuint) data.size(),
            IBO,
            true,
            (GLuint) indexes.size(),
            true,
            GL_TRIANGLES,
            data,
            0,
            HowToRender
        };

        return obj;
    }
}