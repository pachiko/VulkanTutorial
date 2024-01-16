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
        createVertexBuffer();
        createCommandBuffers();
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
    bool framebufferResized = false;
    friend static void framebufferResizeCallback(GLFWwindow* window, int width, int height);


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
    std::vector<VkCommandBuffer> commandBuffers; //freed when commandPool is freed
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;


    /*
        Vertex
    */
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;


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
    void recreateSwapChain();
    void cleanupSwapChain();


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
    void createCommandBuffers();
    void createSyncObjects();


    /*
        Vertex
    */
    void createVertexBuffer();


    /*
        Memory
    */
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);


    /*
        Draw
    */
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void drawFrame();
};