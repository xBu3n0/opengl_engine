#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) || defined(__BORLANDC__)
#include <windows.h>
#define SPRINTF sprintf_s
#define CLEAR "cls"
#else
#define SPRINTF sprintf
#define CLEAR "clear"
#endif

#include "glad/glad.h"
#include "src/Mesh/Mesh.hpp"
#include "src/Shader/Shader.hpp"
#include "src/Window/Window.hpp"

#include <chrono>
#include <map>
#include <stack>
#include <vector>
#include <iostream>

#include <thread>

/**     COMO NÃO ESTÁ IMPLEMENTADO A CAMERA, O CUBO VAI APARECER APENAS A PARTE FRONTAL, FICANDO COMO UM ALGORITMO DE QUADRADO      **/

std::map<std::string, std::vector<GLfloat>> new_triangle;

shader::Shader emptyShader;


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
    // windows["Secondary"] = new window::Window();

    shader::Shader s[2];

    if(windows["Primary"]->InitWindow("Main", 600, 400, false, false) == window::FAILURE) return -1;
    windows["Primary"]->meshes.AddCube(glm::vec3(0.0f, 0.0f, 0.0f), 10.0f, "cubo_1");
    windows["Primary"]->SetBackground(0.2f, 0.3f, 0.3f, 1.0f);

    /*
    if(windows["Secondary"]->InitWindow("Secondary", 300, 600, true, true) == window::FAILURE) return -1;
    
    windows["Secondary"]->meshes.AddCube(glm::vec3(-0.5f, -0.5f, 1.0f), 1.0f, "cubo_1");
    windows["Secondary"]->meshes.AddCube(glm::vec3(0.1f, 0.1f, 1.0f), 0.5f, "cubo_2");
    windows["Secondary"]->SetBackground(0.8f, 0.1f, 0.1f, 1.0f);
    */

    s[0].CreateFromFiles("./shaders/shader.vert",
                        "./shaders/shader.frag", windows["Primary"]->GetWindow());
    windows["Primary"]->meshes.UpdateObjectShader("cubo_1", s[0]);

    s[1].CreateFromFiles("./shaders/triangle.vert",
                        "./shaders/triangle.frag", windows["Primary"]->GetWindow());

    /*
    s[1].CreateFromFiles("./shaders/shader.vert",
                        "./shaders/shader.frag", windows["Secondary"]->GetWindow());
    windows["Secondary"]->meshes.UpdateObjectShader("cubo_1", s[1]);
    windows["Secondary"]->meshes.UpdateObjectShader("cubo_2", s[1]);
    */

    windows["Primary"]->meshes.AddText("00.00 FPS", glm::vec2(10.0f, 10.0f), 0.5f, glm::vec3(0.0f, 0.0f, 0.0f), "FPS");
    shader::Shader tShader;
    tShader.CreateFromFiles("./shaders/tShader.vert",
                            "./shaders/tShader.frag", windows["Primary"]->GetWindow());
    windows["Primary"]->meshes.UpdateTextShader("FPS", tShader);


    // std::thread t(handleInput, std::ref(windows));
    
    int i = 0;
    char aux[20];
    std::map<std::string, bool> release;
    release["Primary"] = true;
    // release["Secondary"] = true;

    while(!windows.empty())
    {
        auto start = std::chrono::steady_clock::now();

        for(std::pair<std::string, window::Window*> x : windows)
            if (x.second->GetStatus() == window::OPENED)
            {
                input::mouse* mouseInfo = x.second->GetInput()->GetMouse();
                int width, height;

                glfwGetWindowSize(x.second->GetWindow(), &width, &height);

                if (mouseInfo->keys[GLFW_MOUSE_BUTTON_LEFT] && release[x.first] == true)
                    new_triangle[x.first].push_back(2.0f * (mouseInfo->lastX - width / 2.0f) / (1.0f * width)),
                    new_triangle[x.first].push_back(2.0f * (height / 2.0f - mouseInfo->lastY) / (1.0f * height)),
                    new_triangle[x.first].push_back(1.0f),
                    release[x.first] = false;
                
                if (!mouseInfo->keys[GLFW_MOUSE_BUTTON_LEFT])
                    release[x.first] = true;

                if (new_triangle[x.first].size() == 9)
                    x.second->meshes.AddTriangle(new_triangle[x.first], "triangulo"),
                    new_triangle.clear(),
                    x.second->meshes.UpdateObjectShader("triangulo", s[1]),
                    std::cout << "Triangulo criado na janela: " << x.first << std::endl;

                x.second->Render();
            }
            else
                willBeClosed.push(x.first);
        
        while(!willBeClosed.empty())
            delete windows[willBeClosed.top()], windows.erase(willBeClosed.top()), willBeClosed.pop();

        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;

        if (windows.count("Primary"))
        {
            SPRINTF(aux, "%.2f FPS", 1 / elapsed_seconds.count());
            windows["Primary"]->meshes.UpdateTextData("FPS", aux);
        }
    }

    system(CLEAR);

    glfwTerminate();
    return 0;
}
