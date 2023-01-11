#include "Cube.hpp"

namespace Eng3D
{
    void HowToRender(struct object::object &obj, bool* keys, struct input::mouse* mouseInfo, camera::Camera *camera)
    {
        obj.shader->UseShader();
        
        
        GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0;
        GLfloat deltaTime = 0.016f;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (600.0f / 400.0f), 0.1f, 1000.0f);
        
        
        camera->KeyControl(keys, deltaTime);
        camera->MouseControl(mouseInfo->xChange, mouseInfo->yChange);
        mouseInfo->xChange = 0.0f;
        mouseInfo->yChange = 0.0f;

        
        uniformModel = obj.shader->uniform["model"].inValue;
        uniformProjection = obj.shader->uniform["projection"].inValue;
        uniformView = obj.shader->uniform["uniformView"].inValue;


        glm::mat4 model(1.0f);

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->CalculateViewMatrix()));
        
        glBindVertexArray(obj.VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.IBO);
        glDrawElements(obj.typeOfRendering, obj.indexCount, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

        std::vector<unsigned int> indexes = {
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
        shader::Shader *shader = new shader::Shader();
        std::map<std::string, struct shader::inInfo     > RequireIn;
        std::map<std::string, struct shader::uniformInfo> RequireUniform;
        std::map<std::string, struct shader::layoutInfo > RequireLayout;

        RequireUniform["model"]         = { "mat4", 0 };
        RequireUniform["projection"]    = { "mat4", 0 };
        RequireUniform["view"]          = { "mat4", 0 };

        RequireLayout["pos"]            = { "(location=0)",  "vec3", "in", 0};

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