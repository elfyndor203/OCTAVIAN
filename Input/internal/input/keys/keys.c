#include "keys_internal.h"
#include "types_internal.h"

#include "cOCT_EngineStructure.h"
#include "input/types.h"

static OCT_keyState iOCT_keyStateList[OCT_KEYS_TOTAL];


OCT_keyState OCT_keyState_read(OCT_key key) {
	return iOCT_keyState_read(key);
}
OCT_keyState iOCT_keyState_read(OCT_key key) {
	return iOCT_keyStateList[key];
}

void iOCT_keyState_set(OCT_key key, OCT_keyState state) {
	iOCT_keyStateList[key] = state;
}