#include "Mesh.hpp"

namespace mesh
{
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