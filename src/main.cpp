#include "glad.h"
#include <GLFW/glfw3.h>
#include <print>
#include <fstream>
#include <sstream>
#include <string>

std::string readFile(const char *path);

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void process_input(GLFWwindow *window);

const unsigned int SCR_HEIGHT{600};
const unsigned int SCR_WIDTH{800};

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

    glfwMakeContextCurrent(window); // bind window context to calling thread
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD");
        return -1;
    }

    // vertex shader
    std::string vertStr{readFile("shader/vertexshader.vert")};
    const char *vertexShaderSource{vertStr.c_str()};
    unsigned int vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    int success;
    char infoLog[512];

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512,NULL, infoLog);
        std::println("ERROR: FAILED TO COMPILE VERTEX SHADER {}", infoLog);
    }

    // fragment shader
    std::string fragStr{readFile("shader/fragmentshader.frag")};
    const char *fragmentShaderSource{fragStr.c_str()};
    unsigned int fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512,NULL, infoLog);
        std::println("ERROR: FAILED TO COMPILE VERTEX SHADER {}", infoLog);
    }

    // link shaders
    unsigned int shaderProgram{glCreateProgram()};
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram,GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::println("ERROR: FAILED TO LINK SHADERS {}", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // vertex data
    float vertices[]{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
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
        std::println("fail to open file {} \n", path);
        return "";
    }
    std::stringstream stream;
    stream << file.rdbuf(); // read buffer to stream
    file.close();
    return stream.str(); // convert to string
}


void process_input(GLFWwindow *window)
{
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
