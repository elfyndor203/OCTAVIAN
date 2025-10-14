#include "update.h"

int updateFrame(GLFWwindow* window) {
    glClearColor(0.5f, 0.5f, 0.5f, 0.5f);   // clears to the bg
    glClear(GL_COLOR_BUFFER_BIT);           // clears the color buffer only

    processInput(window); // process any input 

    if (glfwWindowShouldClose(window)) {
        return 0;
    }
}

int drawLayer(uint shaderProgram, uint VAO, uint VBO) {
    glUseProgram(shaderProgram);       // use the shader program

    
}


    hitBoxVAO = createVertexBuffer(firstVertices, firstVerticesCount);
    glBindVertexArray(hitBoxVAO);
    glDrawArrays(GL_TRIANGLES, 0, firstVerticesCount);

    glfwSwapBuffers(realWindow);
    glfwPollEvents();