#include "Triangle.hpp"

namespace Eng2D
{
    void HowToRender(struct object::object& obj, bool* keys, struct input::mouse* mouseInfo, camera::Camera *camera)
    {
        obj.shader->UseShader();

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

    struct object::object CreateTriangle(std::vector<GLfloat>& data)
    {
        GLuint VAO, VBO, IBO;

        
        std::vector<unsigned int> indexes = {
            0, 1, 2
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indexes.size(), indexes.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        GLuint verticesCount = data.size();
        bool useIBO = true;
        GLuint indexesCount = indexes.size();
        bool willBeRendered = true;
        GLuint typeOfRendering = GL_TRIANGLES;
        shader::Shader  *shader = new shader::Shader();
        std::map<std::string, struct shader::inInfo     > RequireIn;
        std::map<std::string, struct shader::uniformInfo> RequireUniform;
        std::map<std::string, struct shader::layoutInfo > RequireLayout;

        // RequireIn["var"]       = ;
        // RequireUniform["var"]  = ;
        // RequireLayout["var"]   = ;

        glBindVertexArray(0);


        object::object obj = {
            VAO,
            VBO,
            verticesCount,
            IBO,
            useIBO,
            indexesCount,
            willBeRendered,
            typeOfRendering,
            data,
            shader,
            RequireIn,
            RequireUniform,
            RequireLayout,
            HowToRender
        };

        return obj;
    }
}