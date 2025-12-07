#include "vertexData_internal.h"

#include "OCT_Math.h"

OCT_rectangle2D REN_vertices_get(OCT_entityHandle entityHandle, OCT_componentTypes componentType) {
	return iREN_vertices_get(entityHandle.entitySetID, entityHandle.entityID, componentType);
}