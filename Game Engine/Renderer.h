#pragma once
#include <vulkan\vulkan.hpp>
#include <iostream>
#include <map>
#include "Window.h"
#include "VoxelWorld.h"
#include <GLFW\glfw3.h>
#include <set>
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};
class Renderer
{
public:
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec3 up;
	float distOcc;
	bool perspective=true;
	Renderer(GLFWwindow*  win, VoxelWorld _world);
	~Renderer();
	void drawFrame();
	void recreateSwapChain();
private:
	struct QueueFamilyIndices {
		int graphicsFamily = -1;
		int presentFamily = -1;

		inline bool isComplete() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;

	GLFWwindow * win;
	VkSwapchainKHR swapChain;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	VkQueue graphicsQueue, presentQueue;
	VkInstance inst;
	VkPhysicalDevice physicalDevice;
	VkDebugReportCallbackEXT callback;
	VkDevice device;
	VkSemaphore imageAvailableSemaphore;
	VkSemaphore renderFinishedSemaphore;
	VkSurfaceKHR surf;
	VkRenderPass renderPass;
	VkPipeline graphicsPipeline;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	VkDescriptorSetLayout descriptorSetLayout;
	VkPipelineLayout pipelineLayout;
	VkCommandPool commandPool;
	std::vector<VkCommandBuffer> commandBuffers;
	VoxelWorld voxels;
	const std::vector<VertexSingle> cube = {
		{ { -0.5f, -0.5f, 0.5f} },
		{ { 0.5f, -0.5f, 0.5f } },
		{ { 0.5f, 0.5f, 0.5f } },
		{ { -0.5f, 0.5f, 0.5f  } },

		{ { -0.5f, -0.5f, -0.5f } },
		{ { 0.5f, -0.5f, -0.5f  } },
		{ { 0.5f, 0.5f, -0.5f  } },
		{ { -0.5f, 0.5f, -0.5f   } },
	};
	const std::vector<uint16_t> cubeIndex = {
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};
	VkBuffer vertex, instBuf, index, uniform;

	VkDeviceMemory vertexMem, instMem, indexMem, uniformMem;
	std::tuple<double, double, double> plane;
	double side;
	VkDescriptorPool descriptorPool;
	VkDescriptorSet descriptorSet;
	VkImage depthImage;
	VkDeviceMemory depthImageMemory;
	VkImageView depthImageView;
	std::set<VkCommandBuffer> secondaries;

	void cleanupSwapChain();
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void createSemaphores();
	void createCommandBuffers();
	void createCommandPool();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void createRenderPass();
	void createInstance();
	void createDepthResources();
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void setupDebugCallback();
	void createDescriptorSet();
	void addCommandBuffer(VkCommandBuffer buf);
	void removeCommandBuffer(VkCommandBuffer buf);
	VkCommandBuffer getSecondaryBuffer();
	void createFramebuffers();
	VkFormat findDepthFormat();
	VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
	void recordCommandBuffers();
	void createQueueFamilies();
	void pickPhysicalDevice();
	void createDescriptorSetLayout();
	void createDescriptorPool();
	void createVertexBuffers();
	void updateUniformBuffer();
	void createLogicalDevice();
	void createImageViews();
	void createGraphicsPipeline();
	VkShaderModule createShaderModule(const std::vector<char>& code);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
	void createSwapChain();
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	int getDeviceScore(VkPhysicalDevice dev);
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData);
	static inline void ErrorCheck(VkResult res, std::string message) {
		if (res == VK_SUCCESS) return;
		std::cerr << res << ":" <<message;
		std::exit(-1);
	}

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	bool checkValidationLayerSupport();
#ifndef _DEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif
	std::vector<const char*> getRequiedExtensions();
};

