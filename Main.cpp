#include "glad/glad.h"
#include "src/Mesh/Mesh.hpp"
#include "src/Shader/Shader.hpp"
#include "src/Window/Window.hpp"
#include "GLFW/glfw3.h"

#include <chrono>
#include <vector>
#include <iostream>

#include <thread>

/**     COMO NÃO ESTÁ IMPLEMENTADO A CAMERA, O CUBO VAI APARECER APENAS A PARTE FRONTAL, FICANDO COMO UM ALGORITMO DE QUADRADO      **/


void handleInput(std::vector<window::Window*>& windows)
{
    using namespace std::chrono_literals;
    int i = 0;

    while(!windows.empty())
    {
        ++i;
        std::cout << "Número de janelas abertas: " << windows.size() << ", i: " << i << std::endl;
        std::this_thread::sleep_for(100ms);
    
        if(i == 50)
            windows[0]->meshes.UpdateObjectShader(0, 0);
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

    shader::Shader s[2];

    if(windows[0]->CreateWindow("Main", 600, 400, true, false) == window::FAILURE) return -1;
    windows[0]->meshes.AddCube(glm::vec3(0.1f, 0.1f, 1.0f), 0.3); 
    windows[0]->SetBackground(0.2, 0.5, 0.3, 1.0);


    if(windows[1]->CreateWindow("Secondary", 300, 600, true, true) == window::FAILURE) return -1;
    windows[1]->meshes.AddCube(glm::vec3(0.1f, 0.1f, 1.0f), 0.5);
    windows[1]->meshes.AddCube(glm::vec3(-0.5f, -0.5f, 1.0f), 0.5);
    windows[1]->SetBackground(0.8, 0.1, 0.1, 1.0);

    s[0].CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/shader.vert",
                    "/home/bueno/Área de trabalho/OPENGL/shaders/shader.frag", windows[0]->GetWindow());
    windows[0]->meshes.UpdateObjectShader(0, s[0].GetShaderID());


    s[1].CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/shader.vert",
                    "/home/bueno/Área de trabalho/OPENGL/shaders/shader.frag", windows[1]->GetWindow());
    windows[1]->meshes.UpdateObjectShader(0, s[1].GetShaderID());
    windows[1]->meshes.UpdateObjectShader(1, s[1].GetShaderID());

    std::thread t(handleInput, std::ref(windows));

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

        std::cout << '\t' << 1/elapsed_seconds.count() << std::endl;
    }

    t.join();

    glfwTerminate();
    return 0;
}