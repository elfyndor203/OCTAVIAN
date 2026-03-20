#include "WDWModule_internal.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window/window_internal.h"

iOCT_WDWModule iOCT_WDWModule_instance = { 0 };

void OCT_WDWModule_init(char* name, unsigned int sizeX, unsigned int sizeY) {
	iOCT_WDWModule_init(name, sizeX, sizeY);
}

void iOCT_WDWModule_init(char* name, unsigned int sizeX, unsigned int sizeY) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(sizeX, sizeY, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	iOCT_WDWModule_instance.windowPtr = window;
}

