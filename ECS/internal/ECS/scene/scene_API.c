#include "ECS/scene/scene_internal.h"

OCT_scene* OCT_scene_get(OCT_sceneID sceneID) {
	return iOCT_scene_get(sceneID);
}
OCT_sceneID OCT_scene_new() {
	return iOCT_scene_new();
}
void OCT_scene_setCurrent(OCT_sceneID sceneID) {
	iOCT_scene_setCurrent(sceneID);
}