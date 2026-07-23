#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main() {

    vec4 texColor = texture(texture1, texCoord);
    vec3 result = lightColor * objectColor;
    fragColor = texture(texture1, texCoord);
}