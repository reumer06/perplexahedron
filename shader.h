
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

    Shader(const char *vertexPath, const char *fragmentPath);
};
#endif //PLXH_SHADER_H
