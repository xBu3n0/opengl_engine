#ifndef MESH_HPP
#define MESH_HPP

#include "../../glad/glad.h"
#include <GLFW/glfw3.h>
#include <vector>

namespace mesh
{
    struct object
    {
        int VAO;

        int VBO;
        int verticesCount;
        
        int IBO;
        bool useIBO;
        int indexCount;
        
        bool willBeRendered;

        std::vector<GLfloat> data;
    };

    const int FAILURE = 0;
    const int SUCCESS = 1;

    class Mesh
    {
    public:
        Mesh();
    
        int AddMesh();
        int UpdateMesh();
        void EnableObject(int index);
        void DisableObject(int index);
        int DeleteMesh();

        void RenderMesh();

    private:
        void RenderObject(struct object& obj);
        std::vector<struct object> objects;
    };
}


#endif