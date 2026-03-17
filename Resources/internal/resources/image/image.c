#include "image_internal.h"
#include "resources/types_internal.h"

#include "OCT_EngineStructure.h"
#include <string.h>

#include "resources/resource/resource_internal.h"
#include "resources/resourceList/resourceList_internal.h"
#include "resources/module/RESModule_internal.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define iOCT_RGBA 4

OCT_handle iOCT_image_loadPNG(const char* path) {
	OCT_ID imageListID = iOCT_resourceList_IDList[iOCT_resourceImage];
	iOCT_resourceList* list = iOCT_resourceList_get(imageListID);

	OCT_index newIndex;
	OCT_ID newID;
	iOCT_resource* newImage;

	newImage = OCT_pool_addTo(&list->pool, &newIndex);
	newID = OCT_IDMap_register(&list->map, newIndex);
	
	newImage->listID = imageListID;
	strncpy(newImage->path, path, iOCT_PATHNAME_MAX - 1);
	newImage->path[iOCT_PATHNAME_MAX - 1] = '\0';
	newImage->resourceID = newID;
	newImage->type = iOCT_resourceImage;

	int width;
	int height;
	int channels;
	unsigned char* pixels = stbi_load(path, &width, &height, &channels, iOCT_RGBA);
	if (!pixels) {
		printf("Failed load\n");
		printf(stbi_failure_reason());
	}

	OCT_handle handle = {
		.subsystem = OCT_subsystem_resources,
		.containerID = imageListID,
		.objectID = newID,
		.type = OCT_handle_image
	};

	//_OCT_sendMessage(OCT_subsystem_renderer, handle, OCT_message_loadImage, pixels);
	for (int i = 0; i < 1000; i++) {
		printf("%d ", pixels[i]);
	}
	return handle;
}
