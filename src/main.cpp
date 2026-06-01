#include "glad.h"
#include <GLFW/glfw3.h>
#include <print>

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window{glfwCreateWindow(800, 600, "PLXH", NULL, NULL)};
  if (window == NULL) {
    std::println("Failed to create GLFW window");
    glfwTerminate();
    return -1;
  }
  return 0;
}