#include "main.h"

running = true;

size_t indices[] = {
	0, 1, 2,  // first triangle (top-left, top-right, bottom-right)
	2, 3, 0   // second triangle (bottom-right, bottom-left, top-left)
};

void main() {
	OCT_window_initialize("Test Game 2", 1920, 1080);


	OCT_sceneID mainScene = OCT_scene_new(OCT_SCENE_CREATE_ROOT);
	OCT_scene_setCurrent(mainScene);
	OCT_gameObjectID testObject = OCT_gameObject_createNew(OCT_ROOT_OBJECT, false);
	OCT_hitBox2D_addNew(testObject);

	uint vertex = OCT_vertexShader_initialize(hitBox2D_vertexShaderSource);
	uint fragment = OCT_fragmentShader_initialize(hitBox2D_fragmentShaderSource);
	uint program = OCT_shaderProgram_create(vertex, fragment);

	OCT_rendererObjectID renderingObject = OCT_rendererObject_new(testObject, componentHitBox2D, program, false);
	OCT_renderObject_TEST_ONLY(renderingObject);

	while (running) {
		glfwPollEvents();
	}
}