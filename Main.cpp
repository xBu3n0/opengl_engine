#include "glad/glad.h"
#include "src/Mesh/Mesh.hpp"
#include "src/Shader/Shader.hpp"
#include "src/Window/Window.hpp"
#include "GLFW/glfw3.h"

#include <chrono>
#include <vector>
#include <iostream>

#include <thread>


void handleInput(std::vector<window::Window*>& windows)
{
    using namespace std::chrono_literals;

    while(!windows.empty())
    {
        std::cout << "Número de janelas abertas: " << windows.size() << std::endl;
        std::this_thread::sleep_for(100ms);
    }

    return;
}

int main()
{
    if(!glfwInit())
    {
        std::cout << "Erro na inicialização do GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    std::vector<window::Window*> windows;
    
    window::addWindow(windows);
    window::addWindow(windows);

    if(windows[0]->CreateWindow("Main", 600, 400, true, false) == window::FAILURE) return -1;
    if(windows[1]->CreateWindow("Secondary", 300, 600, true, true) == window::FAILURE) return -1;

    shader::Shader s;
    s.CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/shader.vert",
                    "/home/bueno/Área de trabalho/OPENGL/shaders/shader.frag");

    windows[0]->SetBackground(0.2, 0.5, 0.3, 1.0);
    windows[1]->SetBackground(0.8, 0.1, 0.1, 1.0);


    windows[0]->meshes.AddCube(glm::vec3(1.0f, 1.0f, -1.0f), 2, s); 
    windows[1]->meshes.AddCube(glm::vec3(1.0f, 1.0f, -1.0f), 2, s);

    // windows[0]->meshes.AddText("x, pos, 1.0f, color", glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
    // windows[1]->meshes.AddText("x, pos, 1.0f, color", glm::vec2(25.0f, 25.0f), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));



    // std::thread t(handleInput, std::ref(windows));

    while(!windows.empty())
    {
        auto start = std::chrono::steady_clock::now();

        for(int i = 0; i < windows.size(); ++i)
        {
            if(windows[i]->GetStatus() == window::OPENED)
            {
                windows[i]->Render();
            }
            else
            {
                delete windows[i];
                windows.erase(windows.begin() + i);
                --i;
            }
        }
    
        // pstd::cout << "------------------------------" << std::endl;
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;

        // std::cout << '\t' << 1/elapsed_seconds.count() << std::endl;
    }

    // t.join();

    glfwTerminate();
    return 0;
}