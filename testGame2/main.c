#include "main.h"

running = true;

size_t indices[] = {
	0, 1, 2,  // first triangle (top-left, top-right, bottom-right)
	2, 3, 0   // second triangle (bottom-right, bottom-left, top-left)
};

int main() {
	OCT_window_initialize("Test Game Renderer", 1080, 1080);
	OCT_initializeShaders();

	OCT_entitySetID mainSet = OCT_entitySet_new();
	OCT_layerID newLayer = OCT_layer_new();

	OCT_entityHandle mainRoot = OCT_entitySet_root(mainSet);

	OCT_entityHandle testObject = OCT_entity_new(mainRoot);
	OCT_hitBox2D_addNew(testObject, newLayer);
	//OCT_hitBox2D_resize(testObject, 15.0, 15.0);


	float size = 1;
	while (running) {
		OCT_position2D_move(testObject, 0.000001, 0.00002);
		OCT_transform2D_rotate(testObject, 1);
		OCT_handleMessages();
		OCT_render(testObject, componentHitBox2D);
		OCT_hitBox2D_resize(testObject, size, size);
		OCT_window_update();
		OCT_window_handleInputs();
	}
	return 0;
}