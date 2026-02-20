#include "_ECS_Output/vertexData.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"
#include <stdio.h>

OCT_rectangle2D _REN_rectVertices_get(OCT_entityHandle entityHandle, OCT_types componentType) {
	switch (componentType) {
	case OCT_typeComponentHitBox2D:
		return iOCT_hitBox2D_generateVertices(entityHandle.entityContextID, entityHandle.entityID);
	default:
		return iOCT_hitBox2D_generateVertices(entityHandle.entityContextID, entityHandle.entityID); // NOTE_CHANGE_DEFAULT
	}
}
