#include "myStandards.h"
#include "renderer/scenes.h"
#include "renderer/rendererObject.h"
#include "renderer/window.h"
#include "shaders/shaders.h"
#include "shaders/hitBoxShaders.h"
#include "Reference/verticesInput.h"

int running = 1;

int main() {
    GLFWwindow* realWindow = initializeWindow("This Is A Test Window");

    unsigned int hitBoxVertexShader = initializeVertexShader(hitBoxVertexShaderSource);
    unsigned int hitBoxFragmentShader = initializeFragmentShader(hitBoxFragmentShaderSource);
    unsigned int hitBoxShaderProgram = createShaderProgram(hitBoxVertexShader, hitBoxFragmentShader);

    size_t myRendererObject = registerObject(1, NEW_VAO, NEW_VBO(TEST_VERTICES, 15), NEW_EBO(TEST_INDICES, 9), true, true);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (running) {

        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);   // clears to the bg
        glClear(GL_COLOR_BUFFER_BIT);           // clears the color buffer only


        glUseProgram(hitBoxShaderProgram);       // use the shader program

        glBindVertexArray(getRendererObjectPool()[myRendererObject].VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(realWindow);
        glfwPollEvents();
        TESTprocessInput(realWindow); // process any input 

        if (glfwWindowShouldClose(realWindow)) {
            break;
        }
    };
}