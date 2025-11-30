#pragma once
#include "standards/ECSStandards.h"
#include "ECS/components/componentTypes/componentTypes.h"

#include "ECS/gameObject/gameObject.h"
#include "ECS/components/position2D/position2D.h"
#include "ECS/components/transform2D/transform2D.h"
#include "ECS/components/hitBox2D/hitBox2D.h"
#include "ECS/components/hitBox2D/hitbox2DVertices.h"

#define OCT_SCENE_CREATE_ROOT SIZE_MAX
#define OCT_ROOT_OBJECT 0

typedef struct iOCT_scene iOCT_scene;

////////////////////////////////////////////////////////// SCENE
iOCT_scene* OCT_scene_get(iOCT_sceneID sceneID);
iOCT_sceneID OCT_scene_new(OCT_gameObjectID rootObject);
void OCT_scene_setCurrent(iOCT_sceneID sceneID);

////////////////////////////////////////////////////////// pools
iOCT_gameObject* OCT_gameObject_getPool();
iOCT_position2D* OCT_position2D_getPool();
iOCT_transform2D* OCT_transform2D_getPool();
iOCT_hitBox2D* OCT_hitBox2D_getPool();

hitBox2DVertices* OCT_hitBox2DVertices_getPool();

////////////////////////////////////////////////////////// objects and components
iOCT_gameObject* OCT_gameObject_get(OCT_gameObjectID objectIndex);
iOCT_gameObject* OCT_gameObject_getParentObject(OCT_gameObjectID objectIndex);
iOCT_position2D* OCT_position2D_get(OCT_gameObjectID objectIndex);
iOCT_transform2D* OCT_transform2D_get(OCT_gameObjectID objectIndex);
iOCT_hitBox2D* OCT_hitBox2D_get(OCT_gameObjectID objectIndex);

// subcomponents													
hitBox2DVertices* OCT_hitBox2DVertices_get(OCT_gameObjectID objectIndex);

////////////////////////////////////////////////////////// counters
iOCT_counter* OCT_gameObject_getCounter();
iOCT_counter* OCT_position2D_getCounter();
iOCT_counter* OCT_transform2D_getCounter();
iOCT_counter* OCT_hitBox2D_getCounter();

iOCT_counter* OCT_hitBox2DVertices_getCounter();