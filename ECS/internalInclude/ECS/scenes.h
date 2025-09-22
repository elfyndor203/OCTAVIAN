#pragma once
#include "myStandards.h"
#include "ECS/gameObjects.h"
#include "ECS/components/position2D.h"
#include "ECS/components/transform2D.h"
#include "ECS/components/hitBox2D.h"

// a scene contains one instance of every pool
typedef struct {
	counter gameObjectsCounter;
	gameObject gameObjectsPool[MAX_GAMEOBJECTS];

	////////////////////////////////////////////////////////// 1 to 1 components
	counter position2DCounter;
	position2D position2DPool[MAX_GAMEOBJECTS]; 
	counter transform2DCounter;
	transform2D transform2DPool[MAX_GAMEOBJECTS];
	counter hitBox2DCounter;
	hitBox2D hitBox2DPool[MAX_GAMEOBJECTS];

	////////////////////////////////////////////////////////// 1 to 1 subcomponents
	counter hitBox2DVerticesCounter;
	hitBox2DVertices hitBox2DVerticesPool[MAX_GAMEOBJECTS];
	//////////////////////////////////////////////////////////
} scene;

extern scene* currentScene;
extern scene mainScene;

////////////////////////////////////////////////////////// pools
gameObject* getGameObjectsPool();
position2D* getPosition2DPool();
transform2D* getTransform2DPool();
hitBox2D* getHitBox2DPool();

hitBox2DVertices* getHitBox2DVerticesPool();

////////////////////////////////////////////////////////// objects and components
gameObject* getGameObject(gameObjectIndex objectIndex);
gameObject* getParentObject(gameObjectIndex objectIndex);
position2D* getPosition2D(gameObjectIndex objectIndex);
transform2D* getTransform2D(gameObjectIndex objectIndex);
hitBox2D* getHitBox2D(gameObjectIndex objectIndex);

// subcomponents													
hitBox2DVertices* getHitBox2DVertices(gameObjectIndex objectIndex);

////////////////////////////////////////////////////////// counters
counter* getGameObjectsCounter();
counter* getPosition2DCounter();
counter* getTransform2DCounter();
counter* getHitBox2DCounter();

counter* getHitBox2DVerticesCounter();