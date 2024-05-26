#include <iostream>
#include <set>
#include <stdexcept>

#include "application.h"
#include "debug.h"


std::vector<const char*> getRequiredInstanceExtensions();
void checkInstanceExtensions(const char* const* reqExtensions, uint32_t reqCount);


void Application::createInstance() {
    // App Info
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO; // Vulkan has an sType so that pNext in the linked-list works (void*)
    appInfo.pApplicationName = "Hello Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Instance Create Info
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Extensions of Vulkan required by GLFW
    auto reqExtensions = getRequiredInstanceExtensions();
    checkInstanceExtensions(reqExtensions.data(), reqExtensions.size());
    createInfo.enabledExtensionCount = static_cast<uint32_t>(reqExtensions.size());
    createInfo.ppEnabledExtensionNames = reqExtensions.data();

    // global validation layers
    // Need a special way to debug create and destroy instance. Put the debug messenger in createInfo.pNext
    if (enableValidationLayers && !checkValidationLayerSupport()) {
        throw std::runtime_error("validation layers requested, but not available!");
    }
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
        populateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    }
    else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    }

    // CREATE!
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
}


std::vector<const char*> getRequiredInstanceExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}


void checkInstanceExtensions(const char* const* reqExtensions, uint32_t reqCount) {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); // List of supported extensions

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout << "available extensions:\n";

    std::set<std::string> supportedExtensions;
    for (const auto& extension : extensions) {
        std::cout << '\t' << extension.extensionName << '\n';
        supportedExtensions.insert(extension.extensionName);
    }

    for (uint32_t i = 0; i < reqCount; i++) {
        std::string name{ reqExtensions[i] };
        if (supportedExtensions.find(name) != supportedExtensions.cend()) {
            std::cout << "FOUND! " << name << "\n";
        }
        else {
            std::cout << "NOT FOUND! " << name << "\n";
        }
    }
}
