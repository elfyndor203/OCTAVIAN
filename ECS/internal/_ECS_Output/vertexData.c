#include "_ECS_Output/vertexData.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"
#include "OCT_Math.h"

OCT_rectangle2D _REN_rectVertices_get(OCT_entityHandle entityHandle, OCT_types componentType) {
	switch (componentType) {
	case OCT_typeComponentHitBox2D:
		return iOCT_hitBox2D_generateVertices(entityHandle.entitySetID, entityHandle.entityID);
	}
}
