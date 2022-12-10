#include "Window.hpp"

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

    int Window::CreateWindow()
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
            return SUCCESS;
        }

        std::cout << "A janela já foi inicializada.\n";
        return ALREADY_EXISTS;
    }

    int Window::CreateWindow(const std::string& title, int width, int height)
    {
        if(status == UNINITIALIZED)
        {
            this->windowTitle = title;
            this->width = width;
            this->height = height;
            myWindow = glfwCreateWindow(width, height, windowTitle.data(), nullptr, nullptr);

            if(myWindow == nullptr)
            {
                std::cout << "Erro na criação da tela";
                return FAILURE;
            }

            status = OPENED;
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

        meshes.Render();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(myWindow);
        glfwPollEvents();

        return status;
    }

    void Window::SetBackground(float red, float green, float blue)
    {
        this->r = red;
        this->g = green;
        this->b = blue;
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