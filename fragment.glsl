#version 330 core
out vec4 FragColour;

in vec3 Normal;
in vec3 FragPos;

uniform int colourMode; // 0 = normal-direction colour, 1 = diffuse lighting

void main()
{
    vec3 norm = normalize(Normal);

    if (colourMode == 0) {
        // Map normal direction to RGB
        // Normal components range from -1 to 1, remap to 0 to 1
        vec3 colour = norm * 0.5 + 0.5;
        FragColour = vec4(colour, 1.0);
    } else {
        // Dot product with light direction — diffuse + facing classification
        vec3 lightDir = normalize(vec3(1.0, 1.0, 1.0));
        float diff = dot(norm, lightDir); // raw dot product, not clamped

        vec3 colour;
        if (diff > 0.0) {
            // Facing toward light — warm tone, brighter with angle
            colour = mix(vec3(0.4, 0.2, 0.1), vec3(1.0, 0.8, 0.4), diff);
        } else {
            // Facing away — cool/dark tone
            colour = mix(vec3(0.05, 0.1, 0.25), vec3(0.2, 0.3, 0.5), diff + 1.0);
        }
        FragColour = vec4(colour, 1.0);
    }
}