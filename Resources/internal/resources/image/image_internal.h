#pragma once
#include "cOCT_EngineStructure.h"

typedef struct OCT_image {
	OCT_ID resourceID;
	unsigned char* pixels;
	int width;
	int height;
	int channels;
} OCT_image;

OCT_handle iOCT_image_load(const char* path);





