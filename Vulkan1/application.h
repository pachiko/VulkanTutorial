#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <vector>


struct QueueFamilyIndices;
struct SwapChainSupportDetails;

class Application {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    void initWindow();

    void initVulkan() {
        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffer();
        createSyncObjects();
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(device);
    }

    void cleanup();

private:
    /*
        Window
    */
    GLFWwindow* window;
    VkSurfaceKHR surface;


    /*
        Instance
    */
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;


    /*
        Device
    */
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;


    /*
        Queue
    */
    VkQueue graphicsQueue;
    VkQueue presentQueue;


    /*
        Swap Chain
    */
    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews; // ImageView can be used as texture but not render target
    std::vector<VkFramebuffer> swapChainFramebuffers;


    /*
        Graphics Pipeline
    */
    VkRenderPass renderPass;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    

    /*
        Command & Sync
    */
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer; //freed when commandPool is freed
    VkSemaphore imageAvailableSemaphore;
    VkSemaphore renderFinishedSemaphore;
    VkFence inFlightFence;


    /*
        Instance
    */
    void createInstance();
    void setupDebugMessenger();
    bool checkValidationLayerSupport();

    /*
        Window
    */
    void createSurface();


    /*
        Device
    */
    void pickPhysicalDevice();
    void createLogicalDevice();
    int rateDeviceSuitability(VkPhysicalDevice device);
    

    /*
        Queue Family
    */
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);


    /*
        Swap Chain
    */
    void createSwapChain();
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);


    /*
        Image
    */
    void createImageViews();
    void createFramebuffers();


    /*
        Render Pipeline
    */
    void createRenderPass();
    void createGraphicsPipeline();


    /*
        Shader
    */
    VkShaderModule createShaderModule(const std::vector<char>& code);


    /*
        Command & sync
    */
    void createCommandPool();
    void createCommandBuffer();
    void createSyncObjects();

    /*
        Draw
    */
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void drawFrame();
};