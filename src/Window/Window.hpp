#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "../Input/Input.hpp"
#include "../Mesh/Mesh.hpp"

#include <GL/gl.h>
#include <GL/glext.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <vector>
#include <string>

namespace window
{
    const int SUCCESS           = 0;
    const int FAILURE           = 1;
    const int CLOSED            = 2;

    const int UNINITIALIZED     = 3;
    const int OPENED            = 4;

    const int ALREADY_EXISTS    = 5;

    struct mouse
    {
        bool mouseFirstMoved;
        GLfloat xChange, yChange, lastX, lastY;
    };

    class Window
    {
    public:
        // Inicializa a Classe
        Window();
        // Destruir a Classe
        ~Window();

        // Cria uma janela pré-definida
        int CreateWindow();
        // Cria uma janela com as especificações fornecidas (armazenado na variavel myWindow)
        int CreateWindow(const std::string& title, int width, int height, bool isResizable, bool isFullscreen);
        // Cor do plano de fundo
        void SetBackground(float red, float green, float blue, float alpha);
        // Renderiza a cena
        int Render();
        // Recebe o status da janela
        int GetStatus();
        // Retorna o endereço da janela
        GLFWwindow *GetWindow();

    public:
        //Handle inputs
        bool* GetKeys();
        struct mouse* GetMouse();
        
        //Meshes
        mesh::Mesh meshes;

    private:
        // Variavel que armazena a janela gerada pela classe
        GLFWwindow *myWindow = nullptr;
        // Propriedades da janela
        std::string windowTitle = "Blank";
        int width = 600;
        int height = 400;
        float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;

        // Fala o status da janela
        int status = UNINITIALIZED;

        //Camera


        //Inputs
        static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
        static void HandleMouse(GLFWwindow* window, double xPos, double yPos);

    private:
        bool keys[1024];
        struct mouse mouseInfo = {
            true,
            0, 0,
            0, 0
        };
    };
}
#endif