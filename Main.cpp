#include "glad/glad.h"
#include "src/Mesh/Mesh.hpp"
#include "src/Shader/Shader.hpp"
#include "src/Window/Window.hpp"
#include "GLFW/glfw3.h"

#include <chrono>
#include <map>
#include <stack>
#include <vector>
#include <iostream>

#include <thread>

/**     COMO NÃO ESTÁ IMPLEMENTADO A CAMERA, O CUBO VAI APARECER APENAS A PARTE FRONTAL, FICANDO COMO UM ALGORITMO DE QUADRADO      **/


void handleInput(std::map<std::string, window::Window*>& windows)
{
    using namespace std::chrono_literals;
    int i = 0;

    while(!windows.empty())
    {
        std::this_thread::sleep_for(100ms);
    
        if(i != windows.size())
        {
            system("clear");
            i = windows.size();

            std::cout << "Janelas abertas:" << std::endl;
            for(auto x : windows)
                std::cout << "\t" << x.first << std::endl;
        }
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

    std::map<std::string, window::Window*> windows;
    std::stack<std::string> willBeClosed;

    windows["Primary"] = new window::Window();
    windows["Secondary"] = new window::Window();

    shader::Shader s[2];

    if(windows["Primary"]->CreateWindow("Main", 600, 400, true, false) == window::FAILURE) return -1;
    windows["Primary"]->meshes.AddCube(glm::vec3(0.1f, 0.1f, 1.0f), 0.3); 
    windows["Primary"]->SetBackground(0.2, 0.5, 0.3, 1.0);


    if(windows["Secondary"]->CreateWindow("Secondary", 300, 600, true, true) == window::FAILURE) return -1;
    
    windows["Secondary"]->meshes.AddCube(glm::vec3(-0.5f, -0.5f, 1.0f), 1.0);
    windows["Secondary"]->meshes.AddCube(glm::vec3(0.1f, 0.1f, 1.0f), 0.5);
    windows["Secondary"]->SetBackground(0.8, 0.1, 0.1, 1.0);

    s[0].CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/shader.vert",
                        "/home/bueno/Área de trabalho/OPENGL/shaders/shader.frag", windows["Primary"]->GetWindow());
    windows["Primary"]->meshes.UpdateObjectShader(0, s[0].GetShaderID());

    s[1].CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/shader.vert",
                        "/home/bueno/Área de trabalho/OPENGL/shaders/shader.frag", windows["Secondary"]->GetWindow());
    windows["Secondary"]->meshes.UpdateObjectShader(0, s[1].GetShaderID());
    windows["Secondary"]->meshes.UpdateObjectShader(1, s[1].GetShaderID());


    windows["Primary"]->meshes.AddText("Este é um texto renderizado usando FREETYPE", glm::vec2(10.0f, 10.0f), 0.5f, glm::vec3(0.0f, 0.0f, 0.0f));
    shader::Shader tShader;
    tShader.CreateFromFiles("/home/bueno/Área de trabalho/OPENGL/shaders/tShader.vert",
                            "/home/bueno/Área de trabalho/OPENGL/shaders/tShader.frag", windows["Primary"]->GetWindow());
    windows["Primary"]->meshes.UpdateTextShader(0, tShader.GetShaderID());


    std::thread t(handleInput, std::ref(windows));

    while(!windows.empty())
    {
        auto start = std::chrono::steady_clock::now();

        for(std::pair<std::string, window::Window*> x : windows)
            if(x.second->GetStatus() == window::OPENED)
                x.second->Render();
            else
                willBeClosed.push(x.first);
        
        while(!willBeClosed.empty())
            delete windows[willBeClosed.top()], windows.erase(willBeClosed.top()), willBeClosed.pop();

        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;

        // std::cout << "\tFPS: " << 1/elapsed_seconds.count() << std::endl;
    }

    t.join();

    system("clear");

    glfwTerminate();
    return 0;
}