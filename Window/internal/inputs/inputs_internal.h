#pragma once

#include "cOCT_EngineStructure.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void iOCT_keyMap_init();
void iOCT_mouseMap_init();
void iOCT_window_callback_keyEvent(GLFWwindow* window, int key, int scancode, int action, int modifiers);
void iOCT_window_callback_mouseEvent(GLFWwindow* window, int key, int action, int modifiers);
void iOCT_window_callback_mouseMove(GLFWwindow* window, double x, double y);