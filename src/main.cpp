#include "glad.h"
#include <GLFW/glfw3.h>
#include <print>
#include <fstream>
#include <sstream>
#include <string>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "gl_Position = vec4(aPos,1.0);\n"
        "}\n";

const char *fragmentShaderSourceRED = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main(){\n"
        "FragColor = vec4(1.0f,0.0f,0.0f,1.0f);\n"
        "}\n";

const char *fragmentShaderSourceYellow = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "FragColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
        "}\n";


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 800, "2 Color SQUARE",NULL,NULL);
    if (window == NULL) {
        std::println("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::println("failed to initialize glfw");
        return -1;
    }

    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    GLuint fragmentShaderRED{glCreateShader(GL_FRAGMENT_SHADER)};
    GLuint fragmentShaderYellow{glCreateShader(GL_FRAGMENT_SHADER)};
    GLuint shaderProgramYellow{glCreateProgram()};
    GLuint shaderProgramRED{glCreateProgram()};

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glShaderSource(fragmentShaderRED, 1, &fragmentShaderSourceRED,NULL);
    glCompileShader(fragmentShaderRED);

    glShaderSource(fragmentShaderYellow, 1, &fragmentShaderSourceYellow,NULL);
    glCompileShader(fragmentShaderYellow);

    glAttachShader(shaderProgramRED, vertexShader);
    glAttachShader(shaderProgramRED, fragmentShaderRED);
    glLinkProgram(shaderProgramRED);

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderRED);
    glDeleteShader(fragmentShaderYellow);

    GLfloat vertices[]{
        0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5, -0.5f, 0.0f
    };

    GLuint indices[]{
        0, 1, 3,
        0, 3, 4,
        0, 2, 4,
        0, 1, 2
    };

    GLuint VBO, VAO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        glUseProgram(shaderProgramRED);
        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, 0);

        glUseProgram(shaderProgramYellow);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *) (6 * sizeof(GLuint)));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgramRED);
    glDeleteProgram(shaderProgramYellow);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
