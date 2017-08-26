#include "Window.h"
#include "Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <random>
#include <sstream>
void cbstuff(GLFWwindow * win, double xpos, double ypos) {
	int width, height;
	static float pitch, yaw;
	glfwGetWindowSize(win, &width, &height);
	Renderer* rend = (Renderer*)glfwGetWindowUserPointer(win);
	glfwSetCursorPos(win, width / 2, height / 2);
	double sensitivity = 0.05;
	xpos -= width / 2;
	ypos -= height / 2;
	xpos *= sensitivity;
	ypos *= -sensitivity;
	yaw += xpos;
	pitch += ypos;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	rend->dir = glm::normalize(front);
	
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch+90.f));
	front.y = sin(glm::radians(pitch+90.f));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch+90.f));

	rend->up = glm::normalize(front);
	
	

}
void inCb(GLFWwindow * win, int key, int scancode, int action, int mods)
{
	
	Renderer* rend = (Renderer*)glfwGetWindowUserPointer(win);
	float speed = 1;
	auto right = glm::normalize(glm::cross(rend->dir, rend->up));
	if (action == GLFW_PRESS||action == GLFW_REPEAT) {
		switch (key) {
		case GLFW_KEY_W:
			rend->pos = rend->pos + speed*rend->dir;
			break;
		case GLFW_KEY_S:
			rend->pos = rend->pos - speed*rend->dir;

		case GLFW_KEY_A:

			rend->pos = rend->pos - speed*right;
			break;
		case GLFW_KEY_D:

			rend->pos = rend->pos + speed*right;
			break;
		case GLFW_KEY_C:
			rend->distOcc += speed;
			break;
		case GLFW_KEY_V:
			rend->distOcc = rend->distOcc - speed < 0 ? 0 : rend->distOcc - speed;
			break;

		}
	}
}
int main() {
	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.f, 1.f);
	int x, y, n;
	std::vector<float> nums;
	for (int i = 1; i <= 5; i++) {
		std::stringstream ss;
		
		ss << "res/000"<<i<<".png";
		unsigned char *data = stbi_load(ss.str().data(), &x, &y, &n, 0);
		std::cout << n <<"," << x;
		
		for (int j = 0; j <y ; j++) {
			for (int k = 0; k < x; k++) {
				float res = data[x*j + k];
				res /= 255.f;
				nums.push_back(res);
			}
		}
	}
	Window win(800, 800, "Engine");
	float arr[100*100];
	int dims[3] = { 5,y,x };
	for (auto i = 0; i < 100 * 100; i++) {
		float temp = i;
		temp /= 1000.0f;
		arr[i] = distribution(generator);
	}
	glfwSetKeyCallback(win.win, inCb);
	VoxelWorld world( dims, nums.data() );
	Renderer rend{win.win, world};

	glfwSetCursorPosCallback(win.win, cbstuff);
	rend.pos = glm::vec3(0.f, 0.f, 5.f);
	rend.dir = glm::vec3(0.f, 0.f, 1.f);
	rend.up = glm::vec3(0.f, 1.f, 0.f);
	while (!glfwWindowShouldClose(win.win)) { 
		
		
		
		
		glfwPollEvents();
		
		rend.drawFrame();
		
		
	}
	//int i = 0;
}