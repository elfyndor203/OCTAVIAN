#include "shader.h"

#include "OCT_Errors.h"
#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>

GLuint iOCT_shader_load(char* path, bool vert) {
	FILE* file;
	long size;
	char* src;
	size_t read;
	GLuint shader;
	if (vert) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	
	file = fopen(path, "rb");
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	rewind(file);

	src = malloc(size + 1);
	if (!src) {
		OCT_logError(EXIT_FAILED_TO_ALLOCATE);
		return 0;
	}
	read = fread(src, 1, size, file);
	src[read] = '\0';

	glShaderSource(shader, 1, &src, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char log[512];
		glGetShaderInfoLog(shader, 512, NULL, log);
		printf("Shader error: %s\n", log);
	}

	printf("Shader loaded\n");
	free(src);
	return shader;
}

GLuint iOCT_shader_createProgram(char* vert, char* frag) {
	GLuint vertShader = iOCT_shader_load(vert, true);
	GLuint fragShader = iOCT_shader_load(frag, false);

	GLuint program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);

	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		char log[512];
		glGetProgramInfoLog(program, 512, NULL, log);
		printf("Program link error: %s\n", log);
	}

	printf("Shader program created\n");
	return program;
}