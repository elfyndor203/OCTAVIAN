#include "vertexData_internal.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"

OCT_rectangle2D iREN_vertices_get(iOCT_entitySetID entitySetID, iOCT_entityID entityID, OCT_componentTypes componentType) {
	switch (componentType) {
	case componentHitBox2D:
		return iOCT_hitBox2D_generateVertices(entitySetID, entityID);
		break;
	default:
		OCT_logError(EXIT_NOT_YET_IMPLEMENTED);
	}
}
