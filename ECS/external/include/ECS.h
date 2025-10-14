#pragma once
#include "ECSStandards.h"
#include "ECStypes.h"

////////////////////////////////////////////////////////// pools
gameObject* getgameObjectPool();
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
counter* getgameObjectCounter();
counter* position2D_getCounter();
counter* transform2D_getCounter();
counter* hitBox2D_getCounter();

counter* hitBox2DVertices_getCounter();
//////////////////////////////////////////////////////////

gameObjectIndex gameObject_createNew(gameObjectIndex parentIndex, bool is3D);
componentIndex position2D_addNew(gameObjectIndex parentIndex);
componentIndex transform2D_AddNew(gameObjectIndex parentIndex);
componentIndex hitBox2D_addNew(gameObjectIndex parentIndex);
void hitBox2D_resize(gameObjectIndex parentIndex, float sizeX, float sizeY);
componentIndex hitBox2D_generateVertices(gameObjectIndex parentIndex);

