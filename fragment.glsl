#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // Simple diffuse lighting with a hardcoded light direction
    vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
    float diff = max(dot(normalize(Normal), lightDir), 0.0);
    vec3 color = vec3(0.8, 0.8, 0.8);
    FragColor = vec4((0.1 + diff) * color, 1.0);
}