#pragma once
#include "ECS/scene/scene.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2DVertices_internal.h"

#define MAX_SCENE 1024

// a scene contains one instance of every pool
typedef struct iOCT_scene{
	iOCT_sceneID sceneID;
	iOCT_gameObject rootObject;

	iOCT_counter gameObjectCounter;
	iOCT_gameObject gameObjectPool[OCT_MAX_GAMEOBJECT];

	////////////////////////////////////////////////////////// 1 to 1 components
	iOCT_counter position2DCounter;
	iOCT_position2D position2DPool[OCT_MAX_GAMEOBJECT]; 
	iOCT_counter transform2DCounter;
	iOCT_transform2D transform2DPool[OCT_MAX_GAMEOBJECT];
	iOCT_counter hitBox2DCounter;
	iOCT_hitBox2D hitBox2DPool[OCT_MAX_GAMEOBJECT];

	////////////////////////////////////////////////////////// 1 to 1 subcomponents
	iOCT_counter hitBox2DVerticesCounter;
	hitBox2DVertices hitBox2DVerticesPool[OCT_MAX_GAMEOBJECT];
	//////////////////////////////////////////////////////////
} iOCT_scene;

////////////////////////////////////////////////////////// scene
iOCT_scene* scenePool[MAX_SCENE];

iOCT_scene* scene_get(sceneID);
iOCT_sceneID scene_new(OCT_gameObjectID rootObject);
void scene_setCurrent(iOCT_sceneID sceneID);


////////////////////////////////////////////////////////// pools
iOCT_gameObject* gameObject_getPool();
iOCT_position2D* position2D_getPool();
iOCT_transform2D* transform2D_getPool();
iOCT_hitBox2D* hitBox2D_getPool();

hitBox2DVertices* hitBox2DVertices_getPool();

////////////////////////////////////////////////////////// objects and components
iOCT_gameObject* gameObject_get(OCT_gameObjectID objectIndex);
iOCT_gameObject* gameObject_getParentObject(OCT_gameObjectID objectIndex);
iOCT_position2D* position2D_get(OCT_gameObjectID objectIndex);
iOCT_transform2D* transform2D_get(OCT_gameObjectID objectIndex);
iOCT_hitBox2D* hitBox2D_get(OCT_gameObjectID objectIndex);

// subcomponents													
hitBox2DVertices* hitBox2DVertices_get(OCT_gameObjectID objectIndex);

////////////////////////////////////////////////////////// counters
iOCT_counter* gameObject_getCounter();
iOCT_counter* position2D_getCounter();
iOCT_counter* transform2D_getCounter();
iOCT_counter* hitBox2D_getCounter();

iOCT_counter* hitBox2DVertices_getCounter();