#include "window_internal.h"

#include "cOCT_EngineStructure.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#include "module/WDWModule_internal.h"

//OCT_handle iOCT_window_open(char* name, unsigned int sizeX, unsigned int sizeY) {
//	GLFWwindow* window = glfwCreateWindow(sizeX, sizeY, name, NULL, NULL);
//	glfwMakeContextCurrent(window);
//
//	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//
//	OCT_handle windowHandle = {
//		.containerID = OCT_subsystem_window,
//		.objectID = 0,
//		.subsystem = OCT_subsystem_window,
//		.type = OCT_handle_window
//	};
//
//	return windowHandle;
//}

void OCT_window_wipe() {
	iOCT_window_wipe();
}
void iOCT_window_wipe() {
	glClearColor(140.0f, 235.0f, 52.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OCT_window_show() {
	iOCT_window_show();
}
void iOCT_window_show() {
	GLFWwindow* window = iOCT_WDWModule_instance.windowPtr;
	glfwSwapBuffers(window);
}