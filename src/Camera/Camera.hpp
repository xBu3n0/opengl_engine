#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include "../../glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


namespace camera
{
    class Camera
    {
    public:
        Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);
        Camera();

        void KeyControl(bool* keys, GLfloat deltaTime);
        void MouseControl(GLfloat xChange, GLfloat yChange);

        glm::mat4 CalculateViewMatrix();

        ~Camera();

    private:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 worldUp = glm::vec3(0.0f, 0.0f, 0.0f);

        GLfloat yaw = 0.0f;
        GLfloat pitch = 0.0f;

        GLfloat moveSpeed = 0.0f;
        GLfloat turnSpeed = 0.0f;

        void Update();
    };
}

#endif