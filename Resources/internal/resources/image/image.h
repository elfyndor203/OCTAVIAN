#pragma once
#include "OCT_EngineStructure.h"
#include "resources/resource/resource.h"

typedef struct OCT_image {
	OCT_ID resourceID;
	unsigned char* pixels;
	int width;
	int height;
	int channels;
} OCT_image;

OCT_handle iOCT_image_loadPNG(const char* path);





