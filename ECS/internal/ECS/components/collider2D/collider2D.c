#include "collider2D_internal.h"
#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"

#include "ECS/entityContext/entityContext_internal.h"

iOCT_collider2D* iOCT_collider2D_get(iOCT_entityContext* context, OCT_ID colliderID) {
    return iOCT_getByID(context, colliderID, OCT_ECSType_collider2D);
}