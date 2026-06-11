#version 330 core
out vec4 fragColor;
in vec4 vecColor;

void main() {
    fragColor = vecColor;
}