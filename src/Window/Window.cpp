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

            glfwMakeContextCurrent(myWindow);
            // glfwSwapInterval(0);

            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                status = FAILURE;
                return status;
            }

            for(int i = 0; i < 1024; ++i)
                this->keys[i] = false;

            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            status = OPENED;

            glfwSetWindowUserPointer(myWindow, this);

            glfwSetKeyCallback(myWindow, HandleKeys);
            glfwSetCursorPosCallback(myWindow, HandleMouse);

            return SUCCESS;

            return SUCCESS;
        }

        std::cout << "A janela já foi inicializada.\n";
        return ALREADY_EXISTS;
    }

    int Window::CreateWindow(const std::string& title, int width, int height, bool isResizable, bool isFullscreen)
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

            glfwMakeContextCurrent(myWindow);
            // glfwSwapInterval(0);

            if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                status = FAILURE;
                return status;
            }

            for(int i = 0; i < 1024; ++i)
                this->keys[i] = false;

            glfwWindowHint(GLFW_RESIZABLE, isResizable);

            status = OPENED;

            glfwSetWindowUserPointer(myWindow, this);

            glfwSetKeyCallback(myWindow, HandleKeys);
            glfwSetCursorPosCallback(myWindow, HandleMouse);

            return SUCCESS;
        }

        std::cout << "A janela já foi inicializada.\n";
        return ALREADY_EXISTS;
    }

    void Window::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
    {
        window::Window* theWindow = static_cast<window::Window*>(glfwGetWindowUserPointer(window));

        if (key >= 0 && key < 1024)
        {
            if (action == GLFW_PRESS)
            {
                theWindow->keys[key] = true;
            }
            else if (action == GLFW_RELEASE)
            {
                theWindow->keys[key] = false;
            }
        }

        return;
    }

    bool* Window::GetKeys()
    {
        return keys;
    }

    struct mouse* Window::GetMouse()
    {
        return &mouseInfo;
    }

    void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
    {
        window::Window* theWindow = static_cast<window::Window*>(glfwGetWindowUserPointer(window));

        if (theWindow->mouseInfo.mouseFirstMoved)
        {
            theWindow->mouseInfo.lastX = xPos;
            theWindow->mouseInfo.lastY = yPos;
            theWindow->mouseInfo.mouseFirstMoved = false;
        }

        theWindow->mouseInfo.xChange = xPos - theWindow->mouseInfo.lastX;
        theWindow->mouseInfo.yChange = theWindow->mouseInfo.lastY - yPos;

        theWindow->mouseInfo.lastX = xPos;
        theWindow->mouseInfo.lastY = yPos;
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


        glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        
        meshes.Render();

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