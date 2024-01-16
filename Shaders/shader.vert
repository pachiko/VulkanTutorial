#version 450

// layout(location=x) assigns indices to the inputs/outputs
// dvec3 uses 64 bits, so multiple slots. Eg:
// layout(location = 0) in dvec3 inPosition;
// layout(location = 2) in vec3 inColor;
// See more on OpenGL wiki

// vertex attributes (per-vertex properties)
layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;

layout(location = 0) out vec3 fragColor;

void main() {
	gl_Position = vec4(inPosition, 0.0, 1.0); // clip-coordinates ie -w to w, but dummy z and w coords
	fragColor = inColor;
}