#include "glad.h"
#include <GLFW/glfw3.h>
#include <print>

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void process_input(GLFWwindow* window);

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window{glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PLXH", NULL, NULL)};
    if (window == NULL) {
        std::println("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD");
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    float vertices[] = {
        0.5f,  0.5f, 0.0f,  // Top-Right
        0.5f, -0.5f, 0.0f,  // Bottom-Right
       -0.5f, -0.5f, 0.0f,  // Bottom-Left
       -0.5f,  0.5f, 0.0f   // Top-Left
   };

    glfwTerminate();
    return 0;
}

void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}
