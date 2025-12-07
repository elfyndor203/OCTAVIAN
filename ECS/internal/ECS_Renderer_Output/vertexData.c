#include "vertexData_internal.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"

OCT_box2D iREN_hitBox2DVertices_get(iOCT_entitySetID entitySetID, iOCT_entityID entityID) {
	return iOCT_hitBox2D_generateVertices(entitySetID, entityID);
}
