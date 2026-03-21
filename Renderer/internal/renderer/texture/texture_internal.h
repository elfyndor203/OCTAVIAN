#pragma once

#include "cOCT_EngineStructure.h"
#include <glad/glad.h>

GLuint iOCT_texture2D_load(unsigned char* pixels, int width, int height, OCT_handle resourceHandle);
GLuint iOCT_texture2D_get(OCT_handle resourceHandle);