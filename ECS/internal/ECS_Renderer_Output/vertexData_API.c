#include "vertexData_internal.h"

#include "OCT_Math.h"

OCT_box2D REN_hitBox2DVertices_get(OCT_entityHandle entityHandle) {
	iOCT_entitySetID entitySetID = entityHandle.entitySetID;
	iOCT_entityID entityID = entityHandle.entityID;
	return iREN_hitBox2DVertices_get(entitySetID, entityID);
}