#include "glad.h"
#include <GLFW/glfw3.h>
#include <print>
#include <fstream>
#include <sstream>
#include <string>

std::string readFile(const GLchar *path);

void framebuffer_size_callback(GLFWwindow *window, GLint width, GLint height);

void process_input(GLFWwindow *window);

const GLuint SCR_HEIGHT{600};
const GLuint SCR_WIDTH{800};

GLint main()
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

    glEnable(GL_DEPTH_TEST);

    // vertex shaders
    std::string vertStr{readFile("shaders/vertexshader.vert")};
    const GLchar *vertexShaderSource{vertStr.c_str()};
    GLuint vertexShader{glCreateShader(GL_VERTEX_SHADER)};
    glShaderSource(vertexShader, 1, &vertexShaderSource,NULL);
    glCompileShader(vertexShader);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(vertexShader,GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512,NULL, infoLog);
        std::println("ERROR: FAILED TO COMPILE VERTEX SHADER {}", infoLog);
    }

    // fragment shaders
    std::string fragStr{readFile("shaders/fragmentshader.frag")};
    const GLchar *fragmentShaderSource{fragStr.c_str()};
    GLuint fragmentShader{glCreateShader(GL_FRAGMENT_SHADER)};
    glShaderSource(fragmentShader, 1, &fragmentShaderSource,NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader,GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512,NULL, infoLog);
        std::println("ERROR: FAILED TO COMPILE FRAGMENT SHADER {}", infoLog);
    }

    // link shaders
    GLuint shaderProgram{glCreateProgram()};
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
    GLfloat vertices[]{
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, 0.0f, 0.0f
    };
    GLuint indices[]{
        0, 3, 4,
        4, 2, 1,
        0, 1, 4,
        3, 4, 2
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // update the uniform color
        GLfloat timeValue{static_cast<GLfloat>(glfwGetTime())};
        GLfloat colorValue{
            sin(timeValue) / 2.0f + 0.5f // value stays between 0.0f to 1.0f
        };
        GLint vertexColorLocation{glGetUniformLocation(shaderProgram, "vecColor")};
        glUniform4f(vertexColorLocation, colorValue, 0.0f, colorValue, 1.0f);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 16, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // int attribute;        // get the max amount of separate layout inputs you can pass into shader
    // glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &attribute);
    // std::println("{}", attribute);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}


std::string readFile(const GLchar *path)
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
    if (glfwGetKey(window,GLFW_KEY_J) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow *window, GLint width, GLint height)
{
    glViewport(0, 0, width, height);
}
