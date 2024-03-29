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
        createDescriptorSetLayout();
        createGraphicsPipeline();
        createCommandPool();
        createColorResources();
        createDepthResources();
        createFramebuffers();
        createTextureImage();
        createTextureImageView();
        createTextureSampler();
        loadModel();
        createVertexBuffer();
        createIndexBuffer();
        createUniformBuffers();
        createDescriptorPool();
        createDescriptorSets();
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

    /*
        Images
    */
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews; // ImageView can be used as texture but not render target
    std::vector<VkFramebuffer> swapChainFramebuffers;


    /*
        Texture
    */
    uint32_t mipLevels;
    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;


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
        Buffers
    */
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;


    /*
        Uniforms
    */
    VkDescriptorSetLayout descriptorSetLayout;
    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;


    /*
        Sampling
    */
    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;


    /*
        Color
    */
    VkImage colorImage;
    VkDeviceMemory colorImageMemory;
    VkImageView colorImageView;


    /*
        Depth
    */
    VkImage depthImage; // Only 1, since draw 1
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;


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
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
    void createImageViews();
    void createFramebuffers();
    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
        VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);


    /*
        Texture
    */
    void createTextureImage();
    void createTextureImageView();
    void createTextureSampler();
    void generateMipmaps(VkImage image, VkFormat format, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);



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
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);


    /*
        Model stuff
    */
    void loadModel();


    /*
        Buffers
    */
    void createVertexBuffer();
    void createIndexBuffer();


    /*
        Uniforms
    */
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void updateUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createDescriptorSets();


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


    /*
        Sampling
    */
    VkSampleCountFlagBits getMaxUsableSampleCount();


    /*
        Color
    */
    void createColorResources();


    /*
        Depth
    */
    void createDepthResources();
    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

};