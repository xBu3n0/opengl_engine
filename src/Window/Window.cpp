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
        camera = new camera::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.5f);
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
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            myWindow = glfwCreateWindow(width, height, windowTitle.data(), nullptr, nullptr);

            if(myWindow == nullptr)
            {
                std::cout << "Erro na criação da tela";
                return FAILURE;
            }

            status = OPENED;

            glfwMakeContextCurrent(myWindow);
            glEnable(GL_DEPTH_TEST);
            glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            input = new input::Input(myWindow);
            glfwSwapInterval(1);

            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                status = FAILURE;
                return status;
            }

            status = OPENED;

            return SUCCESS;
        }

        std::cout << "A janela já foi inicializada.\n";
        return ALREADY_EXISTS;
    }

    int Window::InitWindow(const std::string& title, int width, int height, bool isResizable, bool isFullscreen)
    {
        if(status == UNINITIALIZED)
        {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            glfwWindowHint(GLFW_RESIZABLE, isResizable);

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

            glfwSwapInterval(1);

            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                status = FAILURE;
                return status;
            }

            // glEnable(GL_DEPTH_TEST);

            status = OPENED;

            input = new input::Input(myWindow);
            // glfwSetInputMode(myWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetFramebufferSize(myWindow, &width, &height);
        // glViewport(0, 0, width, height);

        meshes.Render(input->GetKeys(), input->GetMouse(), camera);

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

    input::Input* Window::GetInput()
    {
        return input;
    }

    GLFWwindow *Window::GetWindow()
    {
        return myWindow;
    }
}