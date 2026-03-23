#pragma once
#include "input/keys/keys.h"

#include "input/types.h"

OCT_keyState iOCT_keyState_get(OCT_key key);
void iOCT_keyState_set(OCT_key key, OCT_keyState state);