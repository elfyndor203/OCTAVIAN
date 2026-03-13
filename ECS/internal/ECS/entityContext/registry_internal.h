#pragma once
#include "OCT_Math.h"
#include "OCT_ECS.h"

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
typedef struct iOCT_registry {
	OCT_ID entityContextID;	// Context that owns this map

	OCT_counter entityCount;
	OCT_counter capacity;
	OCT_index* map;			// entity graph

	OCT_index* recycleList;	// recycled IDs
	OCT_counter recycleCount;
} iOCT_registry;

iOCT_registry* iOCT_registry_get(OCT_ID contextID);
bool iOCT_registry_allocate(OCT_ID contextID);
OCT_ID iOCT_registry_registerID(OCT_ID contextID);
void iOCT_registry_addEntry(OCT_ID contextID, OCT_ID entityID, OCT_types componentType, OCT_index index);

OCT_index* iOCT_registry_accessU(iOCT_registry* registry, OCT_ID entity, OCT_types componentType);