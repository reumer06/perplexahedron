
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

            vertexCode{vshaderStream.str()};
            fragmentCode{fshaderStream.str()};
        } catch (std::istream::failure &e) {
            std::println("ERROR::SHADER::FAIL TO READ FILE: {}", e.what());
        }
        const GLchar *vShaderCode{vertexCode.c_str()};
        const GLchar *fShaderCode{fragmentCode.c_str()};

        GLuint vertex, fragment;

        vertex{glCreateShader(GL_VERTEX_SHADER)};
        glShaderSource(vertex, 1, &vShaderCode,NULL);
        glCompileShader(vertex);
        checkCompileError{vertex, "VERTEX"};
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
};
#endif
