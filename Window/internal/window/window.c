#include "window_internal.h"

#include "cOCT_EngineStructure.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>
#include <stdio.h>

#include "module/WDWModule_internal.h"

static void iOCT_window_keyEvent(int button, int action, int modifiers);


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
	float targetAspect = iOCT_WDWModule_instance.resolution.x / iOCT_WDWModule_instance.resolution.y;

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

    glViewport(offsetX, offsetY, viewWidth, viewHeight);
}

static void iOCT_window_keyEvent(int key, int action, int modifiers) {
    cOCT_message keyMsg;
    if (action == GLFW_PRESS) {
        keyMsg.messageType = cOCT_MSG_BUTTON_DOWN;
    }
    else if (action == GLFW_RELEASE) {
        keyMsg.messageType = cOCT_MSG_BUTTON_UP;
    }
    else {
        return;
    }
    keyMsg.button_event.button = key;
    keyMsg.button_event.modifiers = modifiers;

    cOCT_message_push(OCT_subsystem_input, keyMsg);
}
#pragma region callbacks
void iOCT_window_callback_resize(GLFWwindow* window, int newWidth, int newHeight) {
    iOCT_window_viewport(newWidth, newHeight);
}

void iOCT_window_callback_keyEvent(GLFWwindow* window, int key, int scancode, int action, int modifiers) {
    iOCT_window_keyEvent(key, action, modifiers);
}

void iOCT_window_callback_mouseEvent(GLFWwindow* window, int key, int action, int modifiers) {
    iOCT_window_keyEvent(key, action, modifiers);
}
#pragma regionend
