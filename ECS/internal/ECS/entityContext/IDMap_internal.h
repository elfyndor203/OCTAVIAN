#pragma once
#include "OCT_Math.h"
#include "OCT_ECS.h"

/// <summary>
/// Maps hold lists of pool array locations, indexed by ID
/// </summary>
typedef struct iOCT_IDMap {
	OCT_ID entityContextID;	// Context that owns this map
	OCT_index* map;				// array of entity to component mapping

	OCT_counter nextID;		// next available ID if none are free for reuse
	OCT_counter freeCount;	// count of reusable IDs
	OCT_ID* freeIDs;		// list of reusable IDs
} iOCT_IDMap;

// entity metaData stored in the map for ease of access
typedef enum {
	iOCT_parent,

	iOCT_metaCount
} iOCT_mapMeta;

iOCT_IDMap* iOCT_IDMap_get(OCT_ID contextID);
OCT_index* iOCT_IDMap_access(OCT_ID contextID, OCT_ID entityID, OCT_types componentType);
bool iOCT_IDMap_allocate(OCT_ID contextID);
OCT_ID iOCT_IDMap_register(OCT_ID contextID);
OCT_ID iOCT_IDMap_addComponent(OCT_ID contextID, OCT_ID entityID, OCT_types componentType);