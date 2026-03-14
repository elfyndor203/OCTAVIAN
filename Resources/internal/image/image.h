#pragma once
#include "OCT_EngineStructure.h"
#include "resource/resource.h"

typedef struct OCT_image {
	OCT_ID resourceID;
	unsigned char* pixels;
	int width;
	int height;
	int channels;
} OCT_image;

OCT_resourceHandle OCT_image_loadPNG(char* path);





