#pragma once
#include "ECS/scene/scene.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/gameObject/gameObject_internal.h"
#include "ECS/components/position2D/position2D_internal.h"
#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/components/hitBox2D/hitBox2D_internal.h"

#define MAX_SCENE 1024

// a scene contains one instance of every pool
typedef struct scene{
	OCT_sceneID sceneID;
	gameObject rootObject;

	OCT_counter gameObjectCounter;
	gameObject gameObjectPool[OCT_MAX_GAMEOBJECT];

	////////////////////////////////////////////////////////// 1 to 1 components
	OCT_counter position2DCounter;
	position2D position2DPool[OCT_MAX_GAMEOBJECT]; 
	OCT_counter transform2DCounter;
	transform2D transform2DPool[OCT_MAX_GAMEOBJECT];
	OCT_counter hitBox2DCounter;
	hitBox2D hitBox2DPool[OCT_MAX_GAMEOBJECT];

	////////////////////////////////////////////////////////// 1 to 1 subcomponents
	OCT_counter hitBox2DVerticesCounter;
	hitBox2DVertices hitBox2DVerticesPool[OCT_MAX_GAMEOBJECT];
	//////////////////////////////////////////////////////////
} scene;

////////////////////////////////////////////////////////// scene
scene* scenePointerPool[MAX_SCENE];

scene* scene_get(sceneID);
OCT_sceneID scene_new(OCT_gameObjectID rootObject);
void scene_setCurrent(OCT_sceneID sceneID);


////////////////////////////////////////////////////////// pools
gameObject* gameObject_getPool();
position2D* position2D_getPool();
transform2D* transform2D_getPool();
hitBox2D* hitBox2D_getPool();

hitBox2DVertices* hitBox2DVertices_getPool();

////////////////////////////////////////////////////////// objects and components
gameObject* gameObject_get(OCT_gameObjectID objectIndex);
gameObject* gameObject_getParentObject(OCT_gameObjectID objectIndex);
position2D* position2D_get(OCT_gameObjectID objectIndex);
transform2D* transform2D_get(OCT_gameObjectID objectIndex);
hitBox2D* hitBox2D_get(OCT_gameObjectID objectIndex);

// subcomponents													
hitBox2DVertices* hitBox2DVertices_get(OCT_gameObjectID objectIndex);

////////////////////////////////////////////////////////// counters
OCT_counter* gameObject_getCounter();
OCT_counter* position2D_getCounter();
OCT_counter* transform2D_getCounter();
OCT_counter* hitBox2D_getCounter();

OCT_counter* hitBox2DVertices_getCounter();