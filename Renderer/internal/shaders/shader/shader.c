#include "shader_internal.h"

#include "shaders/debug/debugShaders.h"

static GLuint iOCT_vertexShader_initialize(const char* vertexShader) {
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("glCreateShader ptr = %p\n", glCreateShader);
    unsigned int newVertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(newVertexShader, 1, &vertexShader, NULL);     // figures out where and what the shader is
    glCompileShader(newVertexShader);                                  // compiles the shader

    // check for shader compile errors
    glGetShaderiv(newVertexShader, GL_COMPILE_STATUS, &success);       //asks if vertexShader's compile status is a success (1)
    if (!success)
    {
        glGetShaderInfoLog(newVertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog);   //prints error log
		OCT_logError(EXIT_VERTEX_SHADER_FAILED);
        return 0;
    }
    else {
        return newVertexShader;
    }
}

static GLuint iOCT_fragmentShader_initialize(const char* fragmentShader) {
    unsigned int newFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(newFragmentShader, 1, &fragmentShader, NULL);
    glCompileShader(newFragmentShader);
    // check for shader compile errors

    glGetShaderiv(newFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(newFragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog);
        OCT_logError(EXIT_FRAGMENT_SHADER_FAILED);
        return 0;
    }
    else {
        return newFragmentShader;
    }
}

static GLuint iOCT_shaderProgram_create(GLuint vertexShader, GLuint fragmentShader) {
    unsigned int newShaderProgram = glCreateProgram();
    glAttachShader(newShaderProgram, vertexShader);    // attach both
    glAttachShader(newShaderProgram, fragmentShader);
    glLinkProgram(newShaderProgram);

    glGetProgramiv(newShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(newShaderProgram, 512, NULL, infoLog);
        printf("ERR_SHADER_LINKING_FAILED %s\n", infoLog);
        OCT_logError(EXIT_SHADER_PROGRAM_FAILED);
        return 0;
    }
    else {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader); // don't need them anymore after being attached
    }

    return newShaderProgram;
}

GLuint* iOCT_initializeShaders() {   // NOTE_DANGEROUS_NO_CHECKS
    iOCT_shaderProgramList[shader_debug] = iOCT_shaderProgram_create(iOCT_vertexShader_initialize(debug_vertexShaderSource), iOCT_fragmentShader_initialize(debug_fragmentShaderSource));
    return iOCT_shaderProgramList;
}