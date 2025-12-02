#include "main.h"

running = true;

size_t indices[] = {
	0, 1, 2,  // first triangle (top-left, top-right, bottom-right)
	2, 3, 0   // second triangle (bottom-right, bottom-left, top-left)
};

void main() {
	OCT_window_initialize("Test Game 2", 1920, 1080);

	OCT_sceneID mainScene = OCT_scene_new();
	OCT_scene_setCurrent(mainScene);
	OCT_gameObjectHandle mainRoot = OCT_scene_getRootHandle(mainScene);

	OCT_gameObjectHandle testObject = OCT_gameObject_createNew(mainRoot);
	OCT_hitBox2D_addNew(testObject);

	OCT_gameObjectHandle childOfTest = OCT_gameObject_createNew(testObject);
	OCT_hitBox2D_addNew(childOfTest);

	OCT_gameObjectHandle otherMainObject = OCT_gameObject_createNew(mainRoot);
	OCT_hitBox2D_addNew(otherMainObject);

	OCT_sceneID otherSceneLmao = OCT_scene_new();
	OCT_gameObjectHandle otherRoot = OCT_scene_getRootHandle(otherSceneLmao);
	
	OCT_gameObjectHandle WAH = OCT_gameObject_createNew(otherRoot);
	OCT_hitBox2D_addNew(WAH);

	OCT_gameObjectHandle wahchild = OCT_gameObject_createNew(WAH);
	

	
	//uint fragment = OCT_fragmentShader_initialize(hitBox2D_fragmentShaderSource);
	//uint program = OCT_shaderProgram_create(vertex, fragment);

	//OCT_rendererObjectID renderingObject = OCT_rendererObject_new(WAH, componentHitBox2D, program, false);
	//OCT_renderObject_TEST_ONLY(renderingObject);
}