#include "cursor_internal.h"

#include "OCT_Math.h"
#include <stdbool.h>

#include "_WDW_Output/_WDW_include.h"
#include "_REN_Output/_REN_include.h"

OCT_vec2 OCT_cursorPos_get(bool virtual) {
	OCT_vec2 pos = OCT_window_cursorPos_get();
	//printf("Coords: %f, %f\n", pos.x, pos.y);
	if (virtual) {
		pos = _OCT_renderer_projectCoords(pos);
	}
	printf("Coords: %f, %f\n", pos.x, pos.y);
	return pos;
}