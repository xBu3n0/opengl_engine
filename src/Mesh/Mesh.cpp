#include "Mesh.hpp"

namespace mesh
{
    Mesh::Mesh()
    {
        
    }

    int Mesh::AddText()
    {
        struct text::Text obj;

        glGenVertexArrays(1, &obj.c.VAO);
        glGenBuffers(1, &obj.c.VBO);
        glBindVertexArray(obj.c.VAO);
        glBindBuffer(GL_ARRAY_BUFFER, obj.c.VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6*4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        texts.push_back(obj);

        return SUCCESS;
    }

    int Mesh::AddMesh()
    {


        return SUCCESS;   
    }

    void Mesh::RenderObject(struct object& obj) 
    {
        if(obj.useIBO == true)
        {
            glBindVertexArray(obj.VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.IBO);
            glDrawElements(GL_TRIANGLES, obj.verticesCount, GL_UNSIGNED_INT, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        else
        {
            glBindVertexArray(obj.VAO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.IBO);
            glDrawArrays(GL_TRIANGLES, 0, obj.indexCount);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        return;
    }

    void Mesh::RenderText(text::Text &tex, shader::Shader &s, std::string& text, float x, float y, float scale, glm::vec3 color)
    {
        // activate corresponding render state
        s.UseShader();
        glUniform3f(glGetUniformLocation(s.ShaderID, "textColor"), color.x, color.y, color.z);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(tex.c.VAO);
        // iterate through all characters
        std::string::const_iterator c;

        for (c = text.begin(); c != text.end(); c++)
        {
            text::Character ch = tex.Characters[*c];
            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;
            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            // update VBO for each character
            float vertices[6][4] = {
                { xpos, ypos + h, 0.0f, 0.0f },
                { xpos, ypos, 0.0f, 1.0f },
                { xpos + w, ypos, 1.0f, 1.0f },
                { xpos, ypos + h, 0.0f, 0.0f },
                { xpos + w, ypos, 1.0f, 1.0f },
                { xpos + w, ypos + h, 1.0f, 0.0f }
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
            x += (ch.Advance >> 6) * scale; // bitshift by 6 (2^6 = 64)
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Mesh::EnableObject(int index)
    {
        objects[index].willBeRendered = true;
    }
    void Mesh::DisableObject(int index)
    {
        objects[index].willBeRendered = false;
    }


    void Mesh::RenderMesh()
    {
        for(struct object obj : objects)
            if(obj.willBeRendered == true)
                RenderObject(obj);
        return;
    }
}