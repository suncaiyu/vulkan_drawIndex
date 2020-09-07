#pragma once
#define GLFW_INCLUDE_VULKAN
// glfw头文件
#include "GLFW/GLFW/glfw3.h"
#include <vector>
#include <set>
// vulkan 的 头文件
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <algorithm>
#include <fstream>

// 是否需要debug
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

struct QueueFamilyIndices {
    int graphicsFamily = -1;
    int presentFamily = -1;

    bool isComplete() {
        return graphicsFamily >= 0 && presentFamily >= 0;
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};


class VulkanUtils
{
public:
    VulkanUtils();
    ~VulkanUtils();
    /*
    * @brief 创建instance的实例
    * @return instance的实例
    */
    static VkInstance CreateInstance();
    /*
    * @brief SetupDebugCallback 创建debug 回调
    * @param instance vulkan的instance
    * @return callback debug信息的回调函数
    */
    static VkDebugReportCallbackEXT SetupDebugCallback(VkInstance instance);
    /*
    * @brief delete Debug的方法回调
    * @param instance
    * @param callback
    * @param pAllocate
    */
    static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
    /*
    * @brief 创建显示窗口的surface
    * @param instance Vulkan对象instance
    * @param window 窗口对象
    * @return 窗口surface
    */
    static VkSurfaceKHR CreateSurface(VkInstance instance, GLFWwindow *window);
    /*
    * @brief 选择最优的物理设备
    * @param instacne vulkan的instacne
    * @param surface 西三十窗口的surface
    * @return 物理设备
    */
    static VkPhysicalDevice PickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
    /*
    * @brief 获取swapchain的各项能力
    * @param device 物理设备
    * @param surface 显示的surface
    * @return swapchain的各项能力
    */
    static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

    /*
    * @brief 创建逻辑设备
    * @param physical 物理设备
    * @surface 窗口的surface
    * @param graphicsQueue 图形工作队列(传地址，会赋值)
    * @param presentQueue 呈现队列(传地址，会赋值)
    */
    static VkDevice CreateLogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkQueue *graphicsQueue, VkQueue *presentQueue);

    /*
    * @brief 创建swapChain
    * @param physicalDevice 物理设备
    * @param surface 窗口的surface
    * @param window 窗口对象
    * @param device 逻辑设备
    * @param swapChainImages swapchain里的VkImage(传地址，需要resize)
    * @param swapChainFormat swapChain支持的格式(传地址，会赋值)
    * @param swapChainExtent swapChain支持的VkExtent2D属性(传地址，会赋值)
    */
    static VkSwapchainKHR CreateSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window, VkDevice device, std::vector<VkImage> *swapChainImages, VkFormat *swapChainImageFormat, VkExtent2D *swapChainExtent);

    /*
    * @param brief 寻找队列簇
    * @param device 逻辑设备
    * @param surface 显示窗口的surface
    * @return 队列簇结构体
    */
    static QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

    static std::vector<VkImageView> CreateImageViews(std::vector<VkImage> swapChainImages, VkFormat swapChainImageFormat, VkDevice device);

    static VkRenderPass CreateRenderPass(VkFormat swapChainImageFormat, VkDevice device);

    static std::vector<VkFramebuffer> CreateFramebuffers(std::vector<VkImageView> swapChainImageViews, VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDevice device);
    static VkCommandPool CreateCommandPool(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkDevice device);
    static void CreateBuffer(VkPhysicalDevice physicalDevice, VkDevice device, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    static uint32_t FindMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);
private:
    static bool checkValidationLayerSupport();
};

