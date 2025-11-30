#pragma once
#include "standards/ECSStandards.h"
#include "ECS/components/componentTypes/componentTypes.h"

#include "ECS/gameObject/gameObject.h"
#include "ECS/components/position2D/position2D.h"
#include "ECS/components/transform2D/transform2D.h"
#include "ECS/components/hitBox2D/hitBox2D.h"

#define OCT_ROOT_OBJECT 0


/// For each scene in the game, there is an OCT_scene that contains pools of each gameObject and each component type in it
/// For these pools, the data is stored directly
/// For the pool of scenes, pointers are stored

typedef struct iOCT_scene OCT_scene;

OCT_scene* OCT_currentScene;

OCT_scene* OCT_scene_get(OCT_sceneID sceneID);
OCT_sceneID OCT_scene_new();
void OCT_scene_setCurrent(OCT_sceneID sceneID);
OCT_gameObjectHandle OCT_scene_getRootHandle(OCT_sceneID sceneID);
