cmake_minimum_required(VERSION 3.28)
project(PLXH)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(glad_lib STATIC glad/glad.c)
target_include_directories(glad_lib PUBLIC glad)

add_executable(program src/main.cpp glad/glad.c)
target_include_directories(program PRIVATE glad headers)
target_link_libraries(program PRIVATE glfw OpenGL::GL glad_lib)