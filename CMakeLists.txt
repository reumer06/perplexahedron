cmake_minimum_required(VERSION 3.28)
project(PLXH)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(/usr/include)
include_directories(glad)

add_executable(program src/main.cpp glad/glad.c)

target_link_libraries(program PRIVATE glfw OpenGL::GL)   