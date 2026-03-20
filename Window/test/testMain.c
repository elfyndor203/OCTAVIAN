#include "window/window_internal.h"
#include "module/WDWModule_internal.h"
#include "cOCT_EngineStructure.h"

int main() {
	iOCT_WDWModule_init();
	OCT_handle window = iOCT_window_open("OTTO OCTAVIAN", 600, 800);

	while (true) {

	};
	return 0;
}

