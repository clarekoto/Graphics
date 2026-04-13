#version 330 core
out vec4 FragColour;
in vec3 uniColour;
uniform float alpha;

void main()
{
    // boost the brightness and add a bloom-like glow
    vec3 glow = uniColour * 3.0;
    glow = clamp(glow, 0.0, 1.0);
    FragColour = vec4(glow, alpha);
}