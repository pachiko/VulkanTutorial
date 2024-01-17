#pragma once
//#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES // fixes alignment issues in memory, but doesnt work for nested structures
// A nested structure must be aligned by the base alignment of its members rounded up to a multiple of 16.
#include <glm/glm.hpp>


// A type of descriptor
// GLM is binary-compatible with GLSL
// A vec3 or vec4 must be aligned by 4N (= 16 bytes), A mat4 matrix must have the same alignment as a vec4.
struct UniformBufferObject {
    //glm::vec2 foo; // 2 x 4 = 8 bytes
    alignas(16) glm::mat4 model; // 4 x 4 x 4 Bytes = 64 Bytes. offset = 0, but changed to 8 by foo. NOT a multiple of 16
    glm::mat4 view; // offset = 64, changed to 72
    glm::mat4 proj; // offset = 128, changed to 134.
};
