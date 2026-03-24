#include "window_internal.h"

#include "cOCT_EngineStructure.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

#include "module/WDWModule_internal.h"

void OCT_window_wipe() {
	iOCT_window_wipe();
}
void iOCT_window_wipe() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void OCT_window_show() {
	iOCT_window_show();
}
void iOCT_window_show() {
	GLFWwindow* window = iOCT_WDWModule_instance.windowPtr;
	glfwSwapBuffers(window);
}

void iOCT_window_viewport(int width, int height) {
	glViewport(0, 0, width, height);

    float aspect = width / height;
	float targetAspect = iOCT_WDWModule_instance.targetResolution.x / iOCT_WDWModule_instance.targetResolution.y;

    int viewWidth, viewHeight, offsetX, offsetY;

    if (aspect > targetAspect) { // too wide
        viewHeight = height;
        viewWidth = (int)(height * targetAspect);
        offsetX = (width - viewWidth) / 2;
        offsetY = 0;

    }
    else { // too tall
        viewWidth = width;
        viewHeight = (int)(width / targetAspect);
        offsetX = 0;
        offsetY = (height - viewHeight) / 2;
    }
    iOCT_WDWModule_instance.windowOffset.x = offsetX;
    iOCT_WDWModule_instance.windowOffset.y = offsetY;

    glViewport(offsetX, offsetY, viewWidth, viewHeight);
}

#pragma region callbacks
void iOCT_window_callback_resize(GLFWwindow* window, int newWidth, int newHeight) {
    iOCT_WDWModule_instance.currentResolution = (OCT_vec2){ newWidth, newHeight };
    iOCT_window_viewport(newWidth, newHeight);
}
#pragma endregion

#pragma region cross-module requests
OCT_vec2 _OCT_window_getResolution(OCT_vec2* viewPortOffset) {
    *viewPortOffset = iOCT_WDWModule_instance.windowOffset;
    return iOCT_WDWModule_instance.currentResolution;
}
#pragma endregion
