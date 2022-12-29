#include "Input.hpp"
#include <GLFW/glfw3.h>
#include <cstdio>

namespace input
{
    Input::Input(GLFWwindow* window)
    {
        myWindow = window;

        for(int i = 0; i < 1024; ++i)
            this->keys[i] = false;

        glfwSetWindowUserPointer(myWindow, this);

        glfwSetKeyCallback(myWindow, HandleKeys);
        glfwSetCursorPosCallback(myWindow, HandleMouse);
    }

    void Input::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
    {
        input::Input* theWindow = static_cast<input::Input*>(glfwGetWindowUserPointer(window));

        if(key >= 0 && key < 1024)
            if(action == GLFW_PRESS)
                theWindow->keys[key] = true;
            else if(action == GLFW_RELEASE)
                theWindow->keys[key] = false;

        return;
    }

    void Input::HandleMouse(GLFWwindow* window, double xPos, double yPos)
    {
        input::Input* theWindow = static_cast<input::Input*>(glfwGetWindowUserPointer(window));

        if(theWindow->mouseInfo.mouseFirstMoved)
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

    bool* Input::GetKeys()
    {
        return keys;
    }

    struct mouse* Input::GetMouse()
    {
        return &mouseInfo;
    }
}