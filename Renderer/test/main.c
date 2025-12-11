#include "main.h"
//#include "standards/rendererStandards_internal.h" // NOTE_TEMP

running = true;

size_t indices[] = {
	0, 1, 2,  // first triangle (top-left, top-right, bottom-right)
	2, 3, 0   // second triangle (bottom-right, bottom-left, top-left)
};

float testIndices[8] = {
	-0.5, -0.5,
	0.5, -0.5,
	0.5, 0.5,
	-0.5, 0.5
};

int main() {
	OCT_window_initialize("Test Game Renderer", 1080, 1080);
	OCT_initializeShaders();

	OCT_entitySetID mainSet = OCT_entitySet_new();
	OCT_layerID newLayer = OCT_layer_new();

	OCT_entityHandle mainRoot = OCT_entitySet_root(mainSet);

	OCT_entityHandle testObject = OCT_entity_new(mainRoot);
	OCT_hitBox2D_addNew(testObject, newLayer);
	//OCT_hitBox2D_resize(testObject, 15.0, 15.0);

	
	float size = 1;
	while (true) {
		OCT_handleRendererMessages();
		OCT_render(testObject, OCT_componentHitBox2D);
		size += 0.05;
		OCT_hitBox2D_resize(testObject, size, size);
		OCT_window_update();
	}
	return 0;
}

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <stdio.h>
//
//typedef struct { float x, y; } GPTvertex2D;
//
//typedef struct {
//    GPTvertex2D bottomLeft;
//    GPTvertex2D bottomRight;
//    GPTvertex2D topRight;
//    GPTvertex2D topLeft;
//} corners;
//
//// Simple shaders
//const char* vertexShaderSrc =
//"#version 330 core\n"
//"layout(location = 0) in vec2 aPos;\n"
//"void main() { gl_Position = vec4(aPos, 0.0, 1.0); }\n";
//
//const char* fragmentShaderSrc =
//"#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main() { FragColor = vec4(0.0, 1.0, 0.0, 1.0); }\n";
//
//int main() {
//    // Initialize GLFW
//    if (!glfwInit()) return -1;
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Hitbox Demo", NULL, NULL);
//    if (!window) { glfwTerminate(); return -1; }
//    glfwMakeContextCurrent(window);
//
//    // Load OpenGL with GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        fprintf(stderr, "Failed to initialize GLAD\n");
//        return -1;
//    }
//
//    // Define hitbox corners
//    corners box = {
//        { -0.5f, -0.5f }, // bottomLeft
//        {  0.5f, -0.5f }, // bottomRight
//        {  0.5f,  0.5f }, // topRight
//        { -0.5f,  0.5f }  // topLeft
//    };
//
//    float* vertices = (float*)&box; // direct pointer to 8 floats
//
//    unsigned int indices[] = { 0,1,2, 0,2,3 }; // two triangles
//
//    // OpenGL setup
//    GLuint VAO, VBO, EBO;
//    glGenVertexArrays(1, &VAO);
//    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);
//
//    glBindVertexArray(VAO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(box), vertices, GL_STATIC_DRAW);
//
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // Compile shaders
//    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &vertexShaderSrc, NULL);
//    glCompileShader(vertexShader);
//
//    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, NULL);
//    glCompileShader(fragmentShader);
//
//    GLuint shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);
//
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//
//    // Render loop
//    while (!glfwWindowShouldClose(window)) {
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // Cleanup
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glDeleteBuffers(1, &EBO);
//    glDeleteProgram(shaderProgram);
//
//    glfwTerminate();
//    return 0;
//}
