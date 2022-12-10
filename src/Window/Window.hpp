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
        int CreateWindow(const std::string& title, int width, int height);
        // Cor do plano de fundo
        void SetBackground(float red, float green, float blue);
        // Renderiza a cena
        int Render();
        // Recebe o status da janela
        int GetStatus();
        // Retorna o endereço da janela
        GLFWwindow *GetWindow();

        //Meshes
        mesh::Mesh meshes;

    private:
        // Propriedades da janela
        std::string windowTitle = "Blank";
        int width = 600;
        int height = 400;
        float r = 0.0f, g = 0.0f, b = 0.0f;

        // Variavel que armazena a janela gerada pela classe
        GLFWwindow *myWindow = nullptr;
        // Fala o status da janela
        int status = UNINITIALIZED;

        //Camera


        //Inputs

    };

    void addWindow(std::vector<Window*>& window);
}
#endif