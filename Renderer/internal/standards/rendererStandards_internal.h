#pragma once
#include "standards/rendererStandards.h"

#include <glad/glad.h>
#define GLFW_STATIC
#include <GLFW/glfw3.h>

#define OCT_GENERIC_FAIL SIZE_MAX
#define iOCT_GET_FAILED OCT_GENERIC_FAIL 

static int success;
static char infoLog[512];
