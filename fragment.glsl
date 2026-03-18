#version 330 core
out vec4 FragColor;
in vec3 uniColor;
in vec3 colourPos;

void main()
{
    FragColor = vec4(uniColor, 1.0);
}
