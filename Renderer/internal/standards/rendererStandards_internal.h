#pragma once
#include "standards/rendererStandards.h"

#include <glad/glad.h>
#define GLFW_STATIC
#include <GLFW/glfw3.h>

#define GENERIC_FAIL SIZE_MAX
#define iOCT_GET_FAILED GENERIC_FAIL 

static int success;
static char infoLog[512];
