#ifndef INPUT_HPP
#define INPUT_HPP

#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

namespace input
{
    struct mouse
    {
        bool mouseFirstMoved;
        GLfloat xChange,    yChange,
                lastX,      lastY;
    };

    class Input
    {
    public:
        Input();
        Input(GLFWwindow* window);

        static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
        static void HandleMouse(GLFWwindow* window, double xPos, double yPos);
        
        bool* GetKeys();
        struct mouse* GetMouse();
    
    private:
        bool keys[1024];
        struct mouse mouseInfo = {
            true,
            0, 0,
            0, 0
        };

        GLFWwindow *myWindow = nullptr;
    };
}

#endif