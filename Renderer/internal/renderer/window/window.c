#include "window_internal.h"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void TESTprocessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        printf("pressed w");
}

void window_initialize(char* windowName, size_t width, size_t height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* newWindow = glfwCreateWindow(width, height, windowName, NULL, NULL);
    if (newWindow == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(newWindow);
    glfwSetFramebufferSizeCallback(newWindow, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        OCT_logError(EXIT_WINDOW_NOT_INITIALIZED);
    }
    printf("GL VERSION AFTER INIT: %s\n", glGetString(GL_VERSION));

}

/// API

void OCT_window_initialize(char* windowName, size_t width, size_t height) {
	window_initialize(windowName, width, height);
}


