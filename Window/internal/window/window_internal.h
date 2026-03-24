#pragma once

#include "cOCT_EngineStructure.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void iOCT_window_wipe();
void iOCT_window_show();
void iOCT_window_viewport(int width, int height);

void iOCT_window_callback_resize(GLFWwindow* window, int newWidth, int newHeight);
