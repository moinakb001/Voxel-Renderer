
#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <string>
class Window
{
public:
	
	Window(int width, int height, std::string title);
	~Window();
	GLFWwindow * win;
	VkSurfaceKHR getSurface(VkInstance inst, VkAllocationCallbacks * alloc);

	bool shouldClose();
private:
	VkAllocationCallbacks cb;
	
	VkSurfaceKHR surface;
	VkInstance inst;
	bool hasSurface;
};

