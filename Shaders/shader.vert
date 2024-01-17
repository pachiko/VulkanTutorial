#version 450

// layout(set = 0, binding = 0) ... to bind multiple DSets. Eg diff MVP per object. Avoid rebinding, more efficient

layout(binding = 0) uniform UniformBufferObject {
    // vec2 foo;
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;


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
	gl_Position =  ubo.proj * ubo.view * ubo.model * vec4(inPosition, 0.0, 1.0); // clip-coordinates ie -w to w, but dummy z and w coords
	// With MVP, the last component may not be 1. And that is ok since it is clip coords.
	// Will have a perspective divide when converted to NDC [-1, 1]
	fragColor = inColor;
}