#include "WDWModule_internal.h"

#include "OCT_Math.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "window/window_internal.h"
#include "inputs/inputs_internal.h"

iOCT_WDWModule iOCT_WDWModule_instance = { 0 };

void OCT_WDWModule_init(char* name, unsigned int width, unsigned int height, OCT_vec4 color) {
	iOCT_WDWModule_init(name, width, height, color);
}

void iOCT_WDWModule_init(char* name, unsigned int width, unsigned int height, OCT_vec4 color) {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwSetFramebufferSizeCallback(window, iOCT_window_callback_resize);
	glfwSetKeyCallback(window, iOCT_window_callback_keyEvent);
	glfwSetMouseButtonCallback(window, iOCT_window_callback_mouseEvent);
	glfwSetCursorPosCallback(window, iOCT_window_callback_mouseMove);

	glClearColor(color.x, color.y, color.z, color.a);

	iOCT_WDWModule_instance.windowPtr = window;
	iOCT_WDWModule_instance.targetResolution = (OCT_vec2){ width, height };
	iOCT_WDWModule_instance.currentResolution = iOCT_WDWModule_instance.targetResolution;
	iOCT_window_viewport(width, height);
	iOCT_keyMap_init();
	iOCT_mouseMap_init();
}

void OCT_WDWModule_startFrame() {
	glfwPollEvents();
}
void OCT_WDWModule_endFrame() {
	iOCT_window_show();
	iOCT_window_wipe();
}

bool OCT_window_closed() {
	if (glfwWindowShouldClose(iOCT_WDWModule_instance.windowPtr)) {
		return true;
	}
	else {
		return false;
	}
}