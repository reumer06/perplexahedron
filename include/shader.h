#ifndef PLXH_SHADER_H
#define PLXH_SHADER_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <print>

class Shader
{
public:
    GLuint ID;

    Shader(const char *vertexPath, const char *fragmentPath)
    {
        std::string vertexCode, fragmentCode;
        std::ifstream vertexShaderSource, fragmentShaderSource;
        vertexShaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragmentShaderSource.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            vertexShaderSource.open(vertexPath);
            fragmentShaderSource.open(fragmentPath);
            std::stringstream vshaderStream, fshaderStream;

            vshaderStream << vertexShaderSource.rdbuf();
            fshaderStream << fragmentShaderSource.rdbuf();

            vertexShaderSource.close();
            fragmentShaderSource.close();

            vertexCode = vshaderStream.str();
            fragmentCode = fshaderStream.str();
        } catch (std::istream::failure &e) {
            std::println("ERROR::SHADER::FAIL TO READ FILE: {}", e.what());
        }
        const GLchar *vShaderCode{vertexCode.c_str()};
        const GLchar *fShaderCode{fragmentCode.c_str()};

        GLuint vertex, fragment;

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode,NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode,NULL);
        glCompileShader(fragment);
        checkCompileErrors(fragment, "FRAGMENT");

        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use()
    {
        glUseProgram(ID);
    }

    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int) value);
    }

    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }

private:
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[512];

        if (type != "PROGRAM") {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderInfoLog(shader, 512, NULL, infoLog);
                std::println("ERROR: FAIL TO COMPILE SHADERS: {} \n infoLog: {}", type, infoLog);
            }
        } else {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success) {
                glGetProgramInfoLog(shader, 512, NULL, infoLog);
                std::println("ERROR: FAIL TO LINK SHADERS: {} \n infoLog: {}", type, infoLog);
            }
        }
    }
};
#endif
