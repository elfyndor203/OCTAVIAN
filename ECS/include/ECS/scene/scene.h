#pragma once
#include "standards/ECSStandards.h"
#include "ECS/components/componentTypes/componentTypes.h"

#include "ECS/gameObject/gameObject.h"
#include "ECS/components/position2D/position2D.h"
#include "ECS/components/transform2D/transform2D.h"
#include "ECS/components/hitBox2D/hitBox2D.h"

////////////////////////////////////////////////////////// pools
gameObject* OCT_gameObject_getPool();
position2D* OCT_position2D_getPool();
transform2D* OCT_transform2D_getPool();
hitBox2D* OCT_hitBox2D_getPool();

hitBox2DVertices* OCT_hitBox2DVertices_getPool();

////////////////////////////////////////////////////////// objects and components
gameObject* OCT_gameObject_get(gameObjectIndex objectIndex);
gameObject* OCT_gameObject_getParentObject(gameObjectIndex objectIndex);
position2D* OCT_position2D_get(gameObjectIndex objectIndex);
transform2D* OCT_transform2D_get(gameObjectIndex objectIndex);
hitBox2D* OCT_hitBox2D_get(gameObjectIndex objectIndex);

// subcomponents													
hitBox2DVertices* OCT_hitBox2DVertices_get(gameObjectIndex objectIndex);

////////////////////////////////////////////////////////// counters
counter* OCT_gameObject_getCounter();
counter* OCT_position2D_getCounter();
counter* OCT_transform2D_getCounter();
counter* OCT_hitBox2D_getCounter();

counter* OCT_hitBox2DVertices_getCounter();