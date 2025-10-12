#include "myStandards.h"
#include "renderer/scenes.h"
#include "renderer/rendererObject.h"
#include "Reference//renderLayer.h"

int running = 1;

int main() {
    GLFWwindow* realWindow = initializeWindow("realWindow");

    unsigned int hitBoxVertexShader = initializeVertexShader(hitBoxVertexShaderSource);
    unsigned int hitBoxFragmentShader = initializeFragmentShader(hitBoxFragmentShaderSource);
    unsigned int hitBoxShaderProgram = createShaderProgram(hitBoxVertexShader, hitBoxFragmentShader);

    unsigned int hitBoxVAO = createVertexBuffer(firstVertices, firstVerticesCount);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (running) {

        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);   // clears to the bg
        glClear(GL_COLOR_BUFFER_BIT);           // clears the color buffer only


        glUseProgram(hitBoxShaderProgram);       // use the shader program

        hitBoxVAO = createVertexBuffer(firstVertices, firstVerticesCount);
        glBindVertexArray(hitBoxVAO);
        glDrawArrays(GL_TRIANGLES, 0, firstVerticesCount);

        glfwSwapBuffers(realWindow);
        glfwPollEvents();
        processInput(realWindow); // process any input 

        if (glfwWindowShouldClose(realWindow)) {
            break;
        }
    };
}