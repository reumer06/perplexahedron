
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
            fragmentShaderSource{fshaderStream.str()};
        } catch (std::istream::failure &e) {
            std::println("ERROR::SHADER::FAIL TO READ FILE: {}", e.what());
        }
    }
};
#endif
