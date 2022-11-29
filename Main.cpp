#include "glad/glad.h"
#include "src/Window/Window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <cstdint>
#include <chrono>
#include <vector>
#include <iostream>

namespace windowName
{
    const int MAIN = 0;
    const int SECONDARY = 1;
}

const int WIDTH = 600, HEIGHT = 400;


int main()
{
    if(!glfwInit())
    {
        std::cout << "a";
        return -1;
    }


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_REFRESH_RATE, 10);


    std::vector<window::Window*> myWindows;

    window::addWindow(myWindows);
    window::addWindow(myWindows);

    myWindows[0]->CreateWindow("Main", 600, 400);
    myWindows[0]->SetBackground(0.2, 0.5, 0.3);
    myWindows[1]->CreateWindow("Secondary", 300, 600);
    myWindows[1]->SetBackground(0.8, 0.1, 0.1);

    for(window::Window *w : myWindows)
    {
        glfwMakeContextCurrent(w->GetWindow());
        glfwSwapInterval(0);
        
        if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
        {
            std::cout << "c";
            return -1;
        }
    }

    std::cout << "Number of windows " << myWindows.size() << std::endl;

    glViewport(0, 0, WIDTH, HEIGHT);


    while(!myWindows.empty())
    {
        auto start = std::chrono::steady_clock::now();
        
        for(int i = 0; i < myWindows.size(); ++i)
        {
            if(myWindows[i]->GetStatus() == window::OPENED)
            {
                myWindows[i]->Render();
            }
            else
            {
                delete myWindows[i];
                myWindows.erase(myWindows.begin() + i);
                --i;
            }
        }
    
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - start;

        std::cout << '\t' << 1/elapsed_seconds.count() << std::endl;
    }


    glfwTerminate();
    return 0;
}