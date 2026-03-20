#pragma once
#include "types_internal.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct iOCT_WDWModule {
	GLFWwindow* windowPtr;
};

extern iOCT_WDWModule iOCT_WDWModule_instance;

void iOCT_WDWModule_init(char* name, unsigned int sizeX, unsigned int sizeY);