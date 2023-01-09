#include "Window.hpp"
#include <GLFW/glfw3.h>

namespace window
{
    void addWindow(std::vector<Window*>& vecWindows)
    {
        window::Window *nextWindow = new window::Window();
        vecWindows.push_back(nextWindow);

        return;
    }

    Window::Window()
    {
    }

    Window::~Window()
    {
        glfwDestroyWindow(myWindow);
        myWindow = nullptr;
        status = CLOSED;    
    }

    int Window::InitWindow()
    {
        if(status == UNINITIALIZED)
        {
            myWindow = glfwCreateWindow(width, height, windowTitle.data(), nullptr, nullptr);

            if(myWindow == nullptr)
            {
                std::cout << "Erro na criação da tela";
                return FAILURE;
            }

            status = OPENED;

            glfwMakeContextCurrent(myWindow);
            glfwSwapInterval(1);

            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                status = FAILURE;
                return status;
            }

            status = OPENED;

            input = new input::Input(myWindow);

            return SUCCESS;
        }

        std::cout << "A janela já foi inicializada.\n";
        return ALREADY_EXISTS;
    }

    int Window::InitWindow(const std::string& title, int width, int height, bool isResizable, bool isFullscreen)
    {
        if(status == UNINITIALIZED)
        {
            glfwWindowHint(GLFW_RESIZABLE, isResizable);
            // glfwWindowHint(GLFW_, isFullscreen);

            this->windowTitle = title;
            this->width = width;
            this->height = height;
            myWindow = glfwCreateWindow(width, height, windowTitle.data(), nullptr, nullptr);

            if(myWindow == nullptr)
            {
                std::cout << "Erro na criação da tela";
                status = FAILURE;
                return status;
            }

            meshes.SetWindow(myWindow);
            glfwMakeContextCurrent(myWindow);
            glfwSwapInterval(0);

            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                status = FAILURE;
                return status;
            }

            status = OPENED;

            input = new input::Input(myWindow);

            return SUCCESS;
        }

        std::cout << "A janela já foi inicializada.\n";
        return ALREADY_EXISTS;
    }

    int Window::Render()
    {
        glfwMakeContextCurrent(myWindow);
        
        if(glfwWindowShouldClose(myWindow))
        {
            std::cout << "Uma janela foi fechada\n";
            status = CLOSED;

            return status;
        }


        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwGetFramebufferSize(myWindow, &width, &height);
        // glViewport(0, 0, width, height);

        meshes.Render(input->GetKeys(), input->GetMouse());

        glfwSwapBuffers(myWindow);
        glfwPollEvents();

        return status;
    }

    void Window::SetBackground(float red, float green, float blue, float alpha)
    {
        this->r = red;
        this->g = green;
        this->b = blue;
        this->a = alpha;
    }

    int Window::GetStatus()
    {
        return status;
    }

    GLFWwindow *Window::GetWindow()
    {
        return myWindow;
    }
}