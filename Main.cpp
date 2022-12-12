#include "glad/glad.h"
#include "src/Shader/Shader.hpp"
#include "src/Window/Window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <chrono>
#include <cstdio>
#include <ostream>
#include <vector>
#include <iostream>

#include <thread>
#include <utility>

namespace windowName
{
    const int MAIN = 0;
    const int SECONDARY = 1;
}

const int WIDTH = 600, HEIGHT = 400;


void handleInput(std::vector<window::Window*>& windows)
{
    std::string t;

    while(!windows.empty())
    {
        std::cout << windows.size() << std::endl;
    }

    return;
}

int main()
{
    if(!glfwInit())
    {
        std::cout << "a";
        return -1;
    }

    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    
    std::vector<window::Window*> windows;
    
    window::addWindow(windows);
    window::addWindow(windows);

    if(windows[0]->CreateWindow("Main", 600, 400) == window::FAILURE)
        return -1;

    windows[0]->SetBackground(0.2, 0.5, 0.3);
    windows[1]->CreateWindow("Secondary", 300, 600);
    windows[1]->SetBackground(0.8, 0.1, 0.1);


    shader::Shader s;
    s.CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/shader.vert",
                    "/home/bueno/Área de trabalho/OPENGL/shaders/shader.frag");
    
    std::cout << "Number of windows " << windows.size() << std::endl;

    glViewport(0, 0, WIDTH, HEIGHT);

    windows[0]->meshes.AddText("x, pos, 1.0f, color", glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));


    while(!windows.empty())
    {
        auto start = std::chrono::steady_clock::now();

        for(int i = 0; i < windows.size(); ++i)
        {
            if(windows[i]->GetStatus() == window::OPENED)
            {
                struct window::mouse* m = windows[i]->GetMouse();
                std::cout << m->mouseFirstMoved << '\t' << m->lastX << ' ' << m->lastY << '\t' << m->xChange << ' ' << m->yChange << std::endl;

                windows[i]->Render();
            }
            else
            {
                delete windows[i];
                windows.erase(windows.begin() + i);
                --i;
            }
        }
    
        std::cout << "------------------------------" << std::endl;

        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;

        // std::cout << '\t' << 1/elapsed_seconds.count() << std::endl;
    }

    glfwTerminate();
    return 0;
}