#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {
    fragColor = texture(texture1, texCoord);
}