#pragma once
#include "renderer/window/window.h"
#include "standards/rendererStandards_internal.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef struct rendererWindow {
	GLFWwindow* glfwWindowPointer;
	size_t width;
	size_t height;
} rendererWindow;

GLFWwindow* currentWindow;

void window_initialize(char* windowName, size_t width, size_t height);

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void TESTprocessInput(GLFWwindow* window);