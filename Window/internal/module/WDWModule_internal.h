#pragma once
#include "types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include "OCT_Input.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct iOCT_WDWModule {
	GLFWwindow* windowPtr;
	OCT_vec2 targetResolution;
	OCT_vec2 currentResolution;
	OCT_vec2 windowOffset;

	OCT_key* keyMap;
	OCT_key* mouseMap;
	OCT_vec2 cursorPos;
	OCT_vec2 cursorDelta;
	OCT_vec2 scrollDelta;
};

extern iOCT_WDWModule iOCT_WDWModule_instance;

void iOCT_WDWModule_init(char* name, unsigned int sizeX, unsigned int sizeY, OCT_vec4 color);