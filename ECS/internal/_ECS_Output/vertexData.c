#include "_ECS_Output/vertexData.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"

OCT_rectangle2D _REN_vertices_getDebug(OCT_entityHandle entityHandle) {
	return iOCT_hitBox2D_generateVertices(entityHandle.entitySetID, entityHandle.entityID);		// NOTE_ADD_OTHER_DEBUG_VECTORS
}
