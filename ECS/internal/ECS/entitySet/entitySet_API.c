#include "ECS/entitySet/entitySet_internal.h"


iOCT_entitySet* OCT_entitySet_get(OCT_entitySetID entitySetID) {
	return iOCT_entitySet_get(entitySetID);
}
OCT_entitySetID OCT_entitySet_new() {
	return iOCT_entitySet_new();
}

OCT_entityHandle OCT_entitySet_root(OCT_entitySetID entitySetID) {
	OCT_entityHandle rootHandle = { entitySetID, 0 };
	return rootHandle;
}