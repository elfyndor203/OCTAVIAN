#include "OCT_Engine.h"

OCT_vec4 black = { 0.0, 0.0, 0.0, 0.5 };

OCT_vec4 noTintSolid = {1.0, 1.0, 1.0, 1.0};
OCT_vec4 wholeTexture = {0.0, 0.0, 1.0, 1.0};

int main() {
	OCT_engine_start("MyGame", 1920, 1080, black, 960, 650, 240, 120, 60);

	OCT_handle myContextRoot;	
	OCT_handle myContext = OCT_entityContext_open(&myContextRoot);	// create a context for entities to live in

	OCT_handle character = OCT_entity_new(myContext);

	OCT_handle myTexture = OCT_image_load("images/gear.png");
	OCT_handle foreground = OCT_layer_open(true, myTexture);		// create a layer with a texture for all sprites it owns

	OCT_sprite2D_add(character, foreground, noTintSolid, wholeTexture, (OCT_vec2) { 49, 27 });

	OCT_vec2 cursor;
	while (!OCT_window_closed()) {
		OCT_WDWModule_startFrame();
		cursor = OCT_cursorPos_read(true);

		if (OCT_keyState_read(OCT_KEY_MOUSE_LEFT) == OCT_KEYSTATE_DOWN) {
			OCT_transform2D_moveTo(character, cursor);
		}

		OCT_engine_tick();
	}

	OCT_engine_stop();
	return 0;
}