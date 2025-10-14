#include "shader.h"

unsigned int vertexShader_initialize(const char* vertexShader) {
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

unsigned int fragmentShader_initialize(const char* fragmentShader) {
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

unsigned int shaderProgram_create(int vertexShader, int fragmentShader) {
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