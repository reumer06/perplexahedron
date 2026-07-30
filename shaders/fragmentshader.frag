#version 330 core
out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D texture1;
uniform vec3 lightColor;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 texColor = vec3(texture(texture1, texCoord));

    vec3 result = ambient * texColor;
    
    fragColor = vec4(result, 1.0);
}