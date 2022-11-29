#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <vector>
#include <string>

namespace window
{
    const int SUCCESS           = 0;
    const int FAILURE           = 1;
    const int CLOSED            = 3;

    const int UNINITIALIZED     = 4;
    const int OPENED            = 5;

    const int ALREADY_EXISTS    = 6;

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
        int CreateWindow(const std::string title, int width, int height);

        void SetBackground(float red, float green, float blue);

        int Render();

        int GetStatus();
        GLFWwindow *GetWindow();
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
    };

    void addWindow(std::vector<Window*>& window);
}
#endif