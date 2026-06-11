#version 330 core
out vec4 fragColor;
uniform vec4 vecColor; // global var

void main() {
    fragColor = vecColor;
}