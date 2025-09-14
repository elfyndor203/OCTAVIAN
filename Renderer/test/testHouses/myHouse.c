#include "test/myhouse.h"

const unsigned int resolutionX = 1920;
const unsigned int resolutionY = 1080;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* houseWindow = glfwCreateWindow(resolutionX, resolutionY, "MyHouse", NULL, NULL);
    if (houseWindow == NULL)
    {
        printf("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(houseWindow);
    glfwSetFramebufferSizeCallback(houseWindow, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);   // assigns id for the vertex shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);     // figures out where and what the shader is
    glCompileShader(vertexShader);                                  // compiles the shader
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);       //asks if vertextShader's compile status is a success (1)
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);       
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);   //prints error log
    }

    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
    }

    // link shaders
    unsigned int houseShaderProgram = glCreateProgram(); // shader program = multiple shaders linked
    glAttachShader(houseShaderProgram, vertexShader);    // attach both
    glAttachShader(houseShaderProgram, fragmentShader);
    glLinkProgram(houseShaderProgram);                   // and link them
    // check for linking errors
    glGetProgramiv(houseShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(houseShaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED %s\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); // don't need them anymore after being attached

    float vertices[] = {                    //actual points to be rendered
     0.0f,  0.75f, 0.0f,  // tip
     0.5f,  0.25f, 0.0f,  // tri base R
    -0.5f,  0.25f, 0.0f,  // tri base L
     0.5f, -0.5f, 0.0f,  // bottom R
    -0.5f, -0.5f, 0.0f,  // bottom L
    };
    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 2, // roof
        1, 2, 3, // room rightx
        2, 3, 4  // room lefts
    };

    unsigned int houseVertexArray; 

    unsigned int houseVertexBuffer;
    unsigned int houseElementBuffer;

    glGenVertexArrays(1, &houseVertexArray);    // create the array and buffers
    glGenBuffers(1, &houseVertexBuffer);
    glGenBuffers(1, &houseElementBuffer);

    glBindVertexArray(houseVertexArray);        //bind the array

    glBindBuffer(GL_ARRAY_BUFFER, houseVertexBuffer);                                   //bind the buffers and set some stuff up
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, houseElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);       // something to do with where vertices are in the shader?
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0); // unbinds
    //glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe

    while (!glfwWindowShouldClose(houseWindow)) {
        vertices[0] += 1.0f;

        processInput(houseWindow); // process any input 

        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);   // clears to the bg
        glClear(GL_COLOR_BUFFER_BIT);           // clears the color buffer only

        glUseProgram(houseShaderProgram);       // use the shader program
        //glBindVertexArray(houseVertexArray);     // bind the buffer in case a different one got bound at some point

        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(houseWindow);
        glfwPollEvents();

    }

    glDeleteVertexArrays(1, &houseVertexArray);
    glDeleteBuffers(1, &houseVertexBuffer);
    glDeleteBuffers(1, &houseElementBuffer);
    glDeleteProgram(houseShaderProgram);

    glfwTerminate();
    return 0;


}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

