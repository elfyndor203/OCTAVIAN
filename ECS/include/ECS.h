#pragma once
#include "myPublicStandards.h"

struct point2D;	// alias for vector2D

typedef size_t gameObjectIndex;
typedef size_t componentIndex;
typedef size_t subcomponentIndex;
typedef size_t counter;

typedef struct scene scene;
typedef struct gameObject gameObject;
typedef struct position2D position2D;
typedef struct transform2D transform2D;
typedef struct hitBox2D hitBox2D;
typedef struct hitBox2DVertices hitBox2DVertices;

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
//////////////////////////////////////////////////////////

gameObjectIndex gameObjectCreateNew(gameObjectIndex parentIndex, bool is3D);
componentIndex position2DAddNew(size_t parentIndex);
componentIndex addNewTransform2D(size_t parentIndex);
componentIndex hitBox2DAddNew(gameObjectIndex parentIndex);
void hitBox2DResize(gameObjectIndex parentIndex, float sizeX, float sizeY);
componentIndex hitBox2DGenerateVertices(gameObjectIndex parentIndex);

