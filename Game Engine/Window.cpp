#include "Window.h"



Window::Window(int wid, int hei, std::string str) :cb()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	win = glfwCreateWindow(wid, hei, str.data(), nullptr, nullptr);
	

}


Window::~Window()
{
	if (hasSurface)vkDestroySurfaceKHR(inst, surface,nullptr );
	glfwDestroyWindow(win);
	glfwTerminate();
}
VkSurfaceKHR Window::getSurface(VkInstance inst, VkAllocationCallbacks* alloc) {
	if (!hasSurface) {
		
		auto res = glfwCreateWindowSurface(inst, win, alloc, &surface);
		if (res != VK_SUCCESS) return nullptr;
		this->inst = inst;
		hasSurface = true;
	}
	return surface;
}

bool Window::shouldClose() {
	glfwPollEvents();
	return glfwWindowShouldClose(win);
}