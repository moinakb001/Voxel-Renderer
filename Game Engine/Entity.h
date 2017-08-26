#pragma once
#include <vulkan\vulkan.h>

class Entity {
public:
	virtual VkCommandBuffer recordCommandBuffer();
	inline void setCommandBuffer(VkCommandBuffer buf) {
		this->buf = buf;
		recordCommandBuffer();
	}

private:
	VkCommandBuffer buf;
};