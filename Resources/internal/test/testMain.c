#include "resources/image/image_internal.h"
#include "resources/module/RESModule_internal.h"
#include <stdio.h>
#include "cOCT_EngineStructure.h"

int main() {
	iOCT_RESModule_init();
	OCT_image image = iOCT_image_load("C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/Resources/internal/test/grey.png");

	return 0;
}