#version 330 core
out vec4 fragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 texColor = vec3(texture(texture1, texCoord));

    vec3 result = ambient * texColor;
    fragColor = vec4(result, 1.0);
}