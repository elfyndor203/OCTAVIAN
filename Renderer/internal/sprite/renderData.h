#pragma once
#include "OCT_Math.h"

struct iOCT_renderData {
	OCT_mat3 transform;
	OCT_vec4 color;
};

GLuint iOCT_renderData_initBuffer(int capacity);
