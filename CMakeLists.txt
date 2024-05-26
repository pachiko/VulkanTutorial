cmake_minimum_required (VERSION 3.8)

project ("VulkanTutorial")

set(CMAKE_CXX_STANDARD 20)

# Add source to this project's executable.
add_executable (VulkanTutorial 
	# source files
	"src/cleanup.cpp"
	"src/command.cpp"
	"src/debug.cpp"
	"src/descriptor.cpp"
	"src/device.cpp"
	"src/draw.cpp"
	"src/image.cpp"
	"src/instance.cpp"
	"src/main.cpp"
	"src/memory.cpp"
	"src/pipeline.cpp"
	"src/queueFamily.cpp"
	"src/shader.cpp"
	"src/ssbo.cpp"
	"src/swapchain.cpp"
	"src/sync.cpp"
	"src/uniform.cpp"
	"src/window.cpp"

	# header files
	"src/application.h"
	"src/command.h"
	"src/debug.h"
	"src/particle.h"
	"src/queueFamily.h"
	"src/shader.h"
	"src/swapchain.h"
	"src/uniform.h"
	"src/window.h"
)

# Third Party Dependencies
find_package(Vulkan REQUIRED)
set(GLFW3_DIR "A:\\ThirdParty\\glfw-3.3.9")
target_include_directories(VulkanTutorial PUBLIC ${Vulkan_INCLUDE_DIR} "${GLFW3_DIR}\\include" "A:\\ThirdParty\\glm-0.9.9.8\\glm")
target_link_libraries(VulkanTutorial PUBLIC ${Vulkan_LIBRARY} "${GLFW3_DIR}\\build\\src\\Debug\\glfw3.lib")

## COMPILE SHADERS
find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

file(GLOB_RECURSE GLSL_SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/shaders/*.frag"
    "${PROJECT_SOURCE_DIR}/shaders/*.vert"
    "${PROJECT_SOURCE_DIR}/shaders/*.comp"
    )

foreach(GLSL ${GLSL_SOURCE_FILES})
  message(STATUS "BUILDING SHADER")
  get_filename_component(FILE_NAME ${GLSL} NAME)
  set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILE_NAME}.spv")
  message(STATUS ${GLSL})
  add_custom_command(
    OUTPUT ${SPIRV}
    COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
    DEPENDS ${GLSL})
  list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
    Shaders 
    DEPENDS ${SPIRV_BINARY_FILES}
    )