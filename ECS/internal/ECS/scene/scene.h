#pragma once
#include "standards/ECSStandards.h"

#include "ECS/gameObject/gameObject.h"
#include "ECS/components/position2D/position2D.h"
#include "ECS/components/transform2D/transform2D.h"
#include "ECS/components/hitBox2D/hitBox2D.h"

// a scene contains one instance of every pool
typedef struct {
	counter gameObjectCounter;
	gameObject gameObjectPool[MAX_gameObject];

	////////////////////////////////////////////////////////// 1 to 1 components
	counter position2DCounter;
	position2D position2DPool[MAX_gameObject]; 
	counter transform2DCounter;
	transform2D transform2DPool[MAX_gameObject];
	counter hitBox2DCounter;
	hitBox2D hitBox2DPool[MAX_gameObject];

	////////////////////////////////////////////////////////// 1 to 1 subcomponents
	counter hitBox2DVerticesCounter;
	hitBox2DVertices hitBox2DVerticesPool[MAX_gameObject];
	//////////////////////////////////////////////////////////
} scene;

extern scene* currentScene;
extern scene mainScene;

////////////////////////////////////////////////////////// pools
gameObject* gameObject_getPool();
position2D* position2D_getPool();
transform2D* transform2D_getPool();
hitBox2D* hitBox2D_getPool();

hitBox2DVertices* getHitBox2DVerticesPool();

////////////////////////////////////////////////////////// objects and components
gameObject* gameObject_get(gameObjectIndex objectIndex);
gameObject* gameObject_getParentObject(gameObjectIndex objectIndex);
position2D* position2D_get(gameObjectIndex objectIndex);
transform2D* transform2D_get(gameObjectIndex objectIndex);
hitBox2D* hitBox2D_get(gameObjectIndex objectIndex);

// subcomponents													
hitBox2DVertices* hitBox2DVertices_get(gameObjectIndex objectIndex);

////////////////////////////////////////////////////////// counters
counter* gameObject_getCounter();
counter* position2D_getCounter();
counter* transform2D_getCounter();
counter* hitBox2D_getCounter();

counter* hitBox2DVertices_getCounter();