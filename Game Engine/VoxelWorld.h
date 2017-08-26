#pragma once
#include <vector>
#include <vulkan\vulkan.h>
#include <glm\glm.hpp>
#include <array>
struct VertexSingle {
	glm::vec3 pos;

	static inline VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 0;
		bindingDescription.stride = sizeof(VertexSingle);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}

	static inline std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions = {};
		attributeDescriptions[0].binding = 0;
		attributeDescriptions[0].location = 0;
		attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(VertexSingle, pos);
		return attributeDescriptions;
	}
};
struct VertexInstanced {
	glm::f32 color;
	glm::vec3 offset;

	static inline VkVertexInputBindingDescription getBindingDescription() {
		VkVertexInputBindingDescription bindingDescription = {};
		bindingDescription.binding = 1;
		bindingDescription.stride = sizeof(VertexInstanced);
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_INSTANCE;
		return bindingDescription;
	}
	static inline std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};

		attributeDescriptions[0].binding = 1;
		attributeDescriptions[0].location = 1;
		attributeDescriptions[0].format = VK_FORMAT_R32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(VertexInstanced, color);

		attributeDescriptions[1].binding = 1;
		attributeDescriptions[1].location = 2;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(VertexInstanced, offset);

		return attributeDescriptions;
	}
};
struct UniformBufferObject {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
	float dist;
};
struct tempColors {
	float col[4];
};


class VoxelWorld {
public:
	VoxelWorld(int size[3], float * data);
	std::vector<VertexInstanced> getData(std::tuple<double, double, double> plane, double side);
	std::vector<VertexInstanced> world{};
};
