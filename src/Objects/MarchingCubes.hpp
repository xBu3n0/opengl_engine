#ifndef MARCHINGCUBES_HPP
#define MARCHINGCUBES_HPP

/*
Source das tabelas + referência:
http://paulbourke.net/geometry/polygonise/ 
*/

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace marchingCubes
{
    struct GRIDCELL
    {
        glm::vec3   p[8];
        double      val[8];
    };

    glm::vec3 vertexInterp(double isolevel, glm::vec3 u, glm::vec3 v, GLfloat u_val, GLfloat v_val);

    void evalGrid(GRIDCELL grid, std::vector<GLfloat> &triangles);

    void createMCubes(GLfloat (*function)(glm::vec3 pos),
                    glm::vec3 startPoint, glm::vec3 endPoint, uint n_partitions);
}

#endif