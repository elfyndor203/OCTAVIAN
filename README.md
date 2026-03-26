# OCTAVIAN (WORK IN PROGRESS)
A simple modular ECS game engine written in C 

OCTAVIAN is a simple game engine designed to make me learn C. It uses a mix of ECS and object style systems to manage game data. Its subsystems are meant to be modular. A simple example game is in zGameTest.

# Libraries
- OpenGL 3.3
- GLAD
- GLFW
- stb_image

## Installation (WIP)
1. Use Windows x64
2. Clone the repo
3. Open in VS 2022 (moving to CMAke soon)
5. Set the game project (e.g. zGameTest) as startup, build, and run

## Getting started
- Init order: Window (WDW), Resource (RES), Renderer, (REN), Entity-component (ECS).

```c
#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_Errors.h"
#include "OCT_ECS.h"
#include "OCT_Renderer.h"
#include "OCT_Resources.h"
#include "OCT_Window.h"
#include "OCT_Input.h"

OCT_vec4 black = { 0.0, 0.0, 0.0, 0.5 };

OCT_vec4 noTintSolid = {1.0, 1.0, 1.0, 1.0};
OCT_vec4 wholeTexture = {0.0, 0.0, 1.0, 1.0};

int main() {
	OCT_WDWModule_init("My Game", 1920, 1080, black);	// start engine
	OCT_RESModule_init();
	OCT_RENModule_init((OCT_vec2) { 960, 540 });
	OCT_ECSModule_init();

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

		OCT_INPModule_update();
		OCT_ECSModule_update();
		OCT_RENModule_update();
		OCT_WDWModule_endFrame();
	}

	OCT_ECSModule_free();	// shut down engine
	OCT_RENModule_free();
	OCT_RESModule_free();
	OCT_WDWModule_free();
}
```



