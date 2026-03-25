#include "physics2D_internal.h"
#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"
#include <string.h>
#include <assert.h>

#include "ECS/entityContext/entityContext_internal.h"

void OCT_physics2D_add(OCT_handle entity, float mass, float inertia, float friction, float restitution) {
	assert(entity.type == OCT_handle_entity);
	iOCT_physics2D_add(iOCT_entityContext_get(entity.containerID), entity.objectID, mass, inertia, friction, restitution);
}
OCT_ID iOCT_physics2D_add(iOCT_entityContext* context, OCT_ID entityID, float mass, float inertia, float friction, float restitution) {
	OCT_ID newID;
	OCT_index newIndex;
	iOCT_physics2D* physics;

	cOCT_pool* pool = iOCT_pool_get(context, OCT_ECSType_physics2D);
	physics = (iOCT_physics2D*)cOCT_pool_addEntry(pool, &newIndex);
	newID = cOCT_IDMap_register(&context->IDMap, newIndex);

	memset(physics, 0, sizeof(iOCT_physics2D));
	physics->parentID = entityID;
	physics->physicsID = newID;
	physics->transformID = iOCT_entity_get(context, entityID)->transformID;

	physics->m = mass;
	physics->I = inertia;
	physics->friction = friction;
	physics->restitution = restitution;

	return newID;
}