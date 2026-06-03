#include "glad.h"
#include <GLFW/glfw3.h>
#include <print>
#include <fstream>
#include <sstream>
#include <string>

std::string readFile(const char* path);
void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void process_input(GLFWwindow* window);

const unsigned int SCR_HEIGHT = 600;
const unsigned int SCR_WIDTH = 800;

int main()
{
    // configure and initialize glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // window creation
    GLFWwindow *window{glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "PLXH", NULL, NULL)};
    if (window == NULL) {
        std::println("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);  // bind window context to calling thread
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD");
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(1.0f,0.0f,1.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}


std::string readFile(const char *path)
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::println("fail to open file {} \n",path);
        return "";
    }
    std::stringstream stream;
    stream << file.rdbuf(); // read buffer to stream
    file.close();
    return stream.str();    // convert to string
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
