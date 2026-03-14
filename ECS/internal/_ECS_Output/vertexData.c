#include "_ECS_Output/vertexData.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"
#include "ECS/types_internal.h"
#include "ECS/entityContext/entityContext_internal.h"
#include <stdio.h>

OCT_rectangle2D _REN_rectVertices_get(OCT_handle entityHandle, OCT_types componentType) {
	iOCT_entityContext* context = iOCT_entityContext_get(entityHandle.ownerID);
	switch (componentType) {
	case OCT_typeComponentHitBox2D:
		return iOCT_hitBox2D_generateVertices(context, entityHandle.objectID);
	default:
		return iOCT_hitBox2D_generateVertices(context, entityHandle.objectID); // NOTE_CHANGE_DEFAULT
	}
}
