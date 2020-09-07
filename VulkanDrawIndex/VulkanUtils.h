#pragma once
#define GLFW_INCLUDE_VULKAN
// glfwͷ�ļ�
#include "GLFW/GLFW/glfw3.h"
#include <vector>
#include <set>
// vulkan �� ͷ�ļ�
#include <vulkan/vulkan_core.h>
#include <iostream>
#include <algorithm>
#include <fstream>

// �Ƿ���Ҫdebug
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
    * @brief ����instance��ʵ��
    * @return instance��ʵ��
    */
    static VkInstance CreateInstance();
    /*
    * @brief SetupDebugCallback ����debug �ص�
    * @param instance vulkan��instance
    * @return callback debug��Ϣ�Ļص�����
    */
    static VkDebugReportCallbackEXT SetupDebugCallback(VkInstance instance);
    /*
    * @brief delete Debug�ķ����ص�
    * @param instance
    * @param callback
    * @param pAllocate
    */
    static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
    /*
    * @brief ������ʾ���ڵ�surface
    * @param instance Vulkan����instance
    * @param window ���ڶ���
    * @return ����surface
    */
    static VkSurfaceKHR CreateSurface(VkInstance instance, GLFWwindow *window);
    /*
    * @brief ѡ�����ŵ������豸
    * @param instacne vulkan��instacne
    * @param surface ����ʮ���ڵ�surface
    * @return �����豸
    */
    static VkPhysicalDevice PickPhysicalDevice(VkInstance instance, VkSurfaceKHR surface);
    /*
    * @brief ��ȡswapchain�ĸ�������
    * @param device �����豸
    * @param surface ��ʾ��surface
    * @return swapchain�ĸ�������
    */
    static SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device, VkSurfaceKHR surface);

    /*
    * @brief �����߼��豸
    * @param physical �����豸
    * @surface ���ڵ�surface
    * @param graphicsQueue ͼ�ι�������(����ַ���ḳֵ)
    * @param presentQueue ���ֶ���(����ַ���ḳֵ)
    */
    static VkDevice CreateLogicalDevice(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkQueue *graphicsQueue, VkQueue *presentQueue);

    /*
    * @brief ����swapChain
    * @param physicalDevice �����豸
    * @param surface ���ڵ�surface
    * @param window ���ڶ���
    * @param device �߼��豸
    * @param swapChainImages swapchain���VkImage(����ַ����Ҫresize)
    * @param swapChainFormat swapChain֧�ֵĸ�ʽ(����ַ���ḳֵ)
    * @param swapChainExtent swapChain֧�ֵ�VkExtent2D����(����ַ���ḳֵ)
    */
    static VkSwapchainKHR CreateSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow *window, VkDevice device, std::vector<VkImage> *swapChainImages, VkFormat *swapChainImageFormat, VkExtent2D *swapChainExtent);

    /*
    * @param brief Ѱ�Ҷ��д�
    * @param device �߼��豸
    * @param surface ��ʾ���ڵ�surface
    * @return ���дؽṹ��
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

