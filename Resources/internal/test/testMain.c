#include "resources/image/image.h"
#include "module/RESModule_internal.h"
#include <stdio.h>
#include "OCT_EngineStructure.h"

int main() {
	iOCT_RESModule_init();
	OCT_handle image = iOCT_image_loadPNG("C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/Resources/internal/test/grey.png");

	return 0;
}