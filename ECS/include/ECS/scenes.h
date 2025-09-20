#pragma once
#include "myStandards.h"
#include "ECS/gameObjects.h"
#include "ECS/components/position2D.h"
#include "ECS/components/transform2D.h"
#include "ECS/components/hitBox2D.h"

// a scene contains one instance of every pool

typedef struct {
	size_t gameObjectsCounter;
	gameObject gameObjectsPool[MAX_GAMEOBJECTS];

	size_t position2DCounter;
	position2D position2DPool[MAX_GAMEOBJECTS];

	size_t transform2DCounter;
	transform2D transform2DPool[MAX_GAMEOBJECTS];

	size_t hitBox2DCounter;
	hitBox2D hitBox2DPool[MAX_GAMEOBJECTS];
} scene;

extern scene* currentScene;

extern scene mainScene;

gameObject* getGameObjectsPool();
position2D* getPosition2DPool();
transform2D* getTransform2DPool();
hitBox2D* getHitBox2DPool();

gameObject* getGameObject(size_t objectIndex);
gameObject* getParentObject(size_t objectIndex);
position2D* getPosition2D(size_t objectIndex);
transform2D* getTransform2D(size_t objectIndex);
hitBox2D* getHitBox2D(size_t objectIndex);

size_t* getGameObjectsCounter();
size_t* getPosition2DCounter();
size_t* getTransform2DCounter();
size_t* getHitBox2DCounter();