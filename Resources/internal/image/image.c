#include "image/image.h"
#include "resource/resource.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define iOCT_RGBA 4

OCT_resourceHandle OCT_image_loadPNG(char* path) {
	OCT_image image = { 0 };
	image.pixels = stbi_load(path, &image.width, &image.height, &image.channels, iOCT_RGBA);

	return (OCT_resourceHandle) { image.resourceID, OCT_resourceImage };
}
