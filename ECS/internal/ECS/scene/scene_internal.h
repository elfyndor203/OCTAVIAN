#pragma once
#include "ECS/scene/scene.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2DVertices_internal.h"

#define iOCT_MAX_SCENES 1024

// a scene contains one instance of every pool
// it is tied to its root object, from which all other objects branch from
typedef struct iOCT_scene{
	iOCT_sceneID sceneID;
	iOCT_gameObject rootObject;

	iOCT_counter gameObjectCounter;
	iOCT_gameObject gameObjectPool[iOCT_DEFAULT_MAX_GAMEOBJECTS];

	////////////////////////////////////////////////////////// 1 to 1 components
	iOCT_counter position2DCounter;
	iOCT_position2D position2DPool[iOCT_DEFAULT_MAX_GAMEOBJECTS]; 
	iOCT_counter transform2DCounter;
	iOCT_transform2D transform2DPool[iOCT_DEFAULT_MAX_GAMEOBJECTS];

	////////////////////////////////////////////////////////// many to 1 components
	iOCT_counter hitBox2DCounter;
	iOCT_hitBox2D hitBox2DPool[iOCT_DEFAULT_MAX_GAMEOBJECTS];
	//////////////////////////////////////////////////////////
} iOCT_scene;

////////////////////////////////////////////////////////// scene
iOCT_scene* OCT_scenePool[iOCT_MAX_SCENES]; /// pointers

iOCT_scene* iOCT_scene_get(iOCT_sceneID sceneID);
iOCT_sceneID iOCT_scene_new();
void iOCT_scene_setCurrent(iOCT_sceneID sceneID);
void iOCT_scene_initialize();

