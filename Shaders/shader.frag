#version 450

layout(location = 0) out vec4 outColor; // gl_FragColor is DEPRECATED. Output is linked to frameBuffer 0

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(binding = 1) uniform sampler2D texSampler;

void main() {
	outColor = texture(texSampler, fragTexCoord); // handles filtering
    	//outColor = vec4(fragTexCoord, 0.0, 1.0); // debug using colors
}