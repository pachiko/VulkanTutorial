#version 450

layout(location = 0) out vec4 outColor; // gl_FragColor is DEPRECATED. Output is linked to frameBuffer 0

layout(location = 0) in vec3 fragColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}