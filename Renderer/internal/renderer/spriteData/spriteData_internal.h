#pragma once
#include "OCT_Math.h"

struct iOCT_spriteData {
	OCT_mat3 transform;
	OCT_vec4 color;
	OCT_rect2 uvRect;
};

GLuint iOCT_renderData_initBuffer(int capacity);
