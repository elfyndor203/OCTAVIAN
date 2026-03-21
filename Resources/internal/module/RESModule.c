#include "RESModule_internal.h"
#include "resources/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "resources/resourceList/resourceList_internal.h"
#include "resources/resource/resource_internal.h"

iOCT_RESModule iOCT_RESModule_instance = { 0 };

void OCT_RESModule_init() {
	iOCT_RESModule_init();
}
void iOCT_RESModule_init() {
	iOCT_RESModule_instance.imageList = iOCT_resourceList_open(iOCT_resourceImage);
	iOCT_RESModule_instance.audioList = iOCT_resourceList_open(iOCT_resourceAudio);
}

void iOCT_RESModule_free() {
	iOCT_resourceList_close(&iOCT_RESModule_instance.imageList);
	iOCT_resourceList_close(&iOCT_RESModule_instance.audioList);
}