#include "renderLayer.h"

int running = 1;

int main() {
    GLFWwindow* realWindow = initializeWindow("realWindow");
    processInput(realWindow); // process any input 

    unsigned int hitBoxVertexShader = initializeVertexShader("hitBoxVertexShaderSource");
    unsigned int hitBoxFragmentShader = initializeFragmentShader("hitBoxFragmentShaderSource");
    unsigned int hitBoxShaderProgram = createShaderProgram(hitBoxVertexShader, hitBoxFragmentShader);


    while (running) {


        glClearColor(0.5f, 0.5f, 0.5f, 0.5f);   // clears to the bg
        glClear(GL_COLOR_BUFFER_BIT);           // clears the color buffer only

        
        glUseProgram(hitBoxShaderProgram);       // use the shader program

        unsigned int hitBoxVAO = createVertexBuffer(firstVertices, firstVerticesCount);
        glBindVertexArray(hitBoxVAO);
        glDrawArrays(GL_TRIANGLES, 0, firstVerticesCount / (3* sizeof(float)));

        glfwSwapBuffers(realWindow);
        glfwPollEvents();

    };
}