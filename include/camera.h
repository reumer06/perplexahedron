#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

enum class Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

inline constexpr float YAW = -90.0f;
inline constexpr float PITCH = 0.0f;
inline constexpr float SPEED = 2.5f;
inline constexpr float SENSITIVITY = 0.1f;
inline constexpr float ZOOM = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW,
           float pitch = PITCH)
        : Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch),
          MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        updateCameraVectors();
    }

    glm::mat4 GetViewMatrix() const
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    glm::vec3 GetPosition() const { return Position; }
    float GetZoom() const { return Zoom; }

    void processKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == Camera_Movement::FORWARD) Position += Front * velocity;
        if (direction == Camera_Movement::BACKWARD) Position -= Front * velocity;
        if (direction == Camera_Movement::LEFT) Position -= Right * velocity;
        if (direction == Camera_Movement::RIGHT) Position += Right * velocity;
        Position.y = 0.0f;
    }

    void processMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        Yaw += xoffset * MouseSensitivity;
        Pitch += yoffset * MouseSensitivity;

        if (constrainPitch) {
            if (Pitch > 89.0f) Pitch = 89.0f;
            if (Pitch < -89.0f) Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void processMouseScroll(float yoffset)
    {
        Zoom -= yoffset;
        if (Zoom < 1.0f) Zoom = 1.0f;
        if (Zoom > 45.0f) Zoom = 45.0f;
    }

private:
    glm::vec3 Position;
    glm::vec3 Front{0.0f, 0.0f, -1.0f};
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    void updateCameraVectors()
    {
        glm::vec3 front;
        front.x = std::cos(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
        front.y = std::sin(glm::radians(Pitch));
        front.z = std::sin(glm::radians(Yaw)) * std::cos(glm::radians(Pitch));
        Front = glm::normalize(front);

        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif
