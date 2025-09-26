#include "reference/renderLayer.h"

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        addToVertices(0.001);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

GLFWwindow* initializeWindow(char* windowName) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* newWindow = glfwCreateWindow(1920, 1080, windowName, NULL, NULL);
    if (newWindow == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        
    }

    glfwMakeContextCurrent(newWindow);
    glfwSetFramebufferSizeCallback(newWindow, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    return newWindow;
}

unsigned int initializeVertexShader(const char* vertexShader) {
    unsigned int newVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(newVertexShader, 1, &vertexShader, NULL);     // figures out where and what the shader is
    glCompileShader(newVertexShader);                                  // compiles the shader
    // check for shader compile errors

    glGetShaderiv(newVertexShader, GL_COMPILE_STATUS, &success);       //asks if vertexShader's compile status is a success (1)
    if (!success)
    {
        glGetShaderInfoLog(newVertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);   //prints error log
    }
    else {
        return newVertexShader;
    }
}

unsigned int initializeFragmentShader(char* fragmentShader) {
    unsigned int newFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(newFragmentShader, 1, &fragmentShader, NULL);
    glCompileShader(newFragmentShader);
    // check for shader compile errors

    glGetShaderiv(newFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(newFragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
    }
    else {
        return newFragmentShader;
    }
}

unsigned int createShaderProgram(int vertexShader, int fragmentShader) {
    unsigned int newShaderProgram = glCreateProgram();
    glAttachShader(newShaderProgram, vertexShader);    // attach both
    glAttachShader(newShaderProgram, fragmentShader);
    glLinkProgram(newShaderProgram);

    glGetProgramiv(newShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(newShaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
    }
    else {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader); // don't need them anymore after being attached
    }

    return newShaderProgram;
}


unsigned int createVertexBuffer(float* layer, unsigned int vertexCount) {
    unsigned int newVertexArray = 0;
    unsigned int newVertexBuffer = 0;

    glGenVertexArrays(1, &newVertexArray);    // create the array and buffers
    glGenBuffers(1, &newVertexBuffer);

    glBindVertexArray(newVertexArray);        //bind the array

    glBindBuffer(GL_ARRAY_BUFFER, newVertexBuffer);                                          //bind the vertex buffer
    glBufferData(GL_ARRAY_BUFFER, vertexCount* 3 * sizeof(float), layer, GL_STATIC_DRAW);    // give info about the array to the buffer

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);            // sets up the vertex position attribute
    glEnableVertexAttribArray(0);

    return newVertexArray;
}