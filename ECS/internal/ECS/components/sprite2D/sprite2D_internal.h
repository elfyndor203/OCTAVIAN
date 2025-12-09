#pragma once
#include "sprite2D_internal.h"

#include "ECS/components/componentTypes/componentTypes_internal.h"
#include "ECS/entity/entity_internal.h"

typedef size_t OCT_assetID;

typedef struct sprite2D {
	iOCT_componentID spriteID;
	iOCT_entityID parentID;

	OCT_vector2D size;
	OCT_assetID assetID; 
};