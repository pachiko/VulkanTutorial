# Add source to this project's executable.
add_executable (VulkanTutorial 
	# source files
	"cleanup.cpp"
	"color.cpp"
	"command.cpp"
	"debug.cpp"
	"depth.cpp"
	"device.cpp"
	"draw.cpp"
	"image.cpp"
	"instance.cpp"
	"main.cpp"
	"model.cpp"
	"memory.cpp"
	"pipeline.cpp"
	"queueFamily.cpp"
	"sampling.cpp"
	"shader.cpp"
	"swapChain.cpp"
	"texture.cpp"
	"uniform.cpp"
	"vertex.cpp"
	"window.cpp"

	# header files
	"application.h"
	"command.h"
	"debug.h"
	"depth.h"
	"draw.h"
	"model.h"
	"queueFamily.h"
	"shader.h"
	"swapChain.h"
	"uniform.h"
	"vertex.h"
	"window.h"
)

# Third Party Dependencies
find_package(Vulkan REQUIRED)
set(GLFW3_DIR "A:\\ThirdParty\\glfw-3.3.9")
target_include_directories(VulkanTutorial PUBLIC 
	${Vulkan_INCLUDE_DIR} 
	"${GLFW3_DIR}\\include"
	"A:\\ThirdParty\\glm-0.9.9.8\\glm"
	"A:\\ThirdParty\\tinyobjloader"
	"A:\\ThirdParty\\stb_image"
)

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