# Add source to this project's executable.
add_executable (VulkanTest "main.cpp")

# Third Party Dependencies
find_package(Vulkan REQUIRED)
set(GLFW3_DIR "A:\\ThirdParty\\glfw-3.3.9")
target_include_directories(VulkanTest PUBLIC ${Vulkan_INCLUDE_DIR} "${GLFW3_DIR}\\include" "A:\\ThirdParty\\glm-0.9.9.8\\glm")
target_link_libraries(VulkanTest PUBLIC ${Vulkan_LIBRARY} "${GLFW3_DIR}\\build\\src\\Debug\\glfw3.lib")
