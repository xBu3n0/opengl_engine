#include "Mesh.hpp"
#include <GLFW/glfw3.h>

namespace mesh
{
    Mesh::Mesh()
    {}

    void Mesh::SetWindow(GLFWwindow *myWindow)
    {
        this->myWindow = myWindow;
    }

    int Mesh::AddCube(glm::vec3 pos, float length, std::string object_name)
    {
        glfwMakeContextCurrent(myWindow);

        objects[object_name] = Eng3D::CreateCube(pos, length);

        return SUCCESS;
    }
    
    int Mesh::AddText(std::string text, glm::vec2 pos, float scale, glm::vec3 color, std::string name)
    {
        glfwMakeContextCurrent(myWindow);

        text::Text obj;

        obj.c.text  = text;
        obj.c.pos   = pos;
        obj.c.scale = scale;
        obj.c.color = color;

        glGenVertexArrays(1, &obj.c.VAO);
        glGenBuffers(1, &obj.c.VBO);
        glBindVertexArray(obj.c.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, obj.c.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6*4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        texts[name] = obj;

        return SUCCESS;
    }

    void Mesh::Render(bool* keys, struct input::mouse* mouseInfo)
    {
        for(std::pair<std::string, struct object::object> x : objects)
            if(x.second.willBeRendered)
                x.second.HowToRender(x.second, keys, mouseInfo);
        for(std::pair<std::string, text::Text> x : texts)
            RenderText(x.second);
    }

    void Mesh::RenderObject(struct object::object& obj) 
    {
        glUseProgram(obj.s);

        if(obj.useIBO)
        {   
            glBindVertexArray(obj.VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.IBO);
            glDrawElements(obj.typeOfRendering, obj.indexCount, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        else
        {
            glBindVertexArray(obj.VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.VBO);
            glDrawArrays(obj.typeOfRendering, 0, static_cast<GLsizei>(obj.data.size()));
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        glUseProgram(0);

        return;
    }

    void Mesh::RenderText(text::Text &tex)
    {
        glUseProgram(tex.s);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // activate corresponding render state
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(600), 0.0f, static_cast<float>(400));
        glUniformMatrix4fv(glGetUniformLocation(tex.s, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glUniform3f(glGetUniformLocation(tex.s, "textColor"), tex.c.color.x, tex.c.color.y, tex.c.color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(tex.c.VAO);

        // iterate through all characters
        std::string::const_iterator c;

        for(c = tex.c.text.begin(); c != tex.c.text.end(); c++)
        {
            text::Character ch = tex.Characters[*c];
            float xpos = tex.c.pos.x + ch.Bearing.x * tex.c.scale;
            float ypos = tex.c.pos.y - (ch.Size.y - ch.Bearing.y) * tex.c.scale;
            float w = ch.Size.x * tex.c.scale;
            float h = ch.Size.y * tex.c.scale;

            // update VBO for each character
            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, tex.c.VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // advance cursors for next glyph (advance is 1/64 pixels)
            tex.c.pos.x += (ch.Advance >> 6) * tex.c.scale; // bitshift by 6 (2^6 = 64)
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    int Mesh::UpdateObjectShader(const char* name, GLuint s)
    {
        if (objects.count(name))
            objects[name].s = s;
        else
            return FAILURE;
        return SUCCESS;
    }

    int Mesh::UpdateTextData(const char* name, const char* text)
    {
        if (texts.count(name))
            texts[name].c.text = text;
        else
            return FAILURE;
        return SUCCESS;
    }

    int Mesh::UpdateTextShader(const char* name, GLuint s)
    {
        if (texts.count(name))
            texts[name].s = s;
        else
            return FAILURE;
        return SUCCESS;
    }


    int Mesh::EnableObject(const char* name)
    {
        if (objects.count(name))
            objects[name].willBeRendered = true;
        else
            return FAILURE;
        return SUCCESS;
    }

    int Mesh::DisableObject(const char* name)
    {
        if (objects.count(name))
            objects[name].willBeRendered = false;
        else
            return FAILURE;
        return SUCCESS;
    }

    int Mesh::DeleteMesh(const char* name)
    {
        if (objects.count(name))
            objects.erase(name);
        else
            return FAILURE;
        return SUCCESS;
    }
}