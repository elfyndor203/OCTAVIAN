#pragma once
#include "ECSStandards.h"
#include "ECStypes.h"

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
componentIndex position2DAddNew(gameObjectIndex parentIndex);
componentIndex transform2DAddNew(gameObjectIndex parentIndex);
componentIndex hitBox2DAddNew(gameObjectIndex parentIndex);
void hitBox2DResize(gameObjectIndex parentIndex, float sizeX, float sizeY);
componentIndex hitBox2DGenerateVertices(gameObjectIndex parentIndex);

