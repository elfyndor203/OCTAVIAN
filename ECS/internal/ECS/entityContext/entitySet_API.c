#include "ECS/entitySet/entitySet_internal.h"


iOCT_entityContext* OCT_entitySet_get(OCT_entitySetID entitySetID) {
	return iOCT_entityContext_get(entitySetID);
}
OCT_entitySetID OCT_entitySet_new() {
	return iOCT_entityContext_open();
}

OCT_entityHandle OCT_entitySet_root(OCT_entitySetID entitySetID) {
	OCT_entityHandle rootHandle = { entitySetID, 0 };
	return rootHandle;
}