#include "standards/rendererStandards_internal.h"
#include "OCT_EngineStructure.h"

void testKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_RIGHT:
			printf("Pressed right arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_active, _OCT_position2D_move, .1f, 0);
			break;
		case GLFW_KEY_LEFT:
			printf("Pressed left arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_active, _OCT_position2D_move, -.1f, 0);
			break;
		case GLFW_KEY_UP:
			printf("Pressed up arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_active, _OCT_position2D_move, 0.0f, 0.1f);
			break;
		case GLFW_KEY_DOWN:
			printf("Pressed down arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_active, _OCT_position2D_move, 0.0f, -0.1f);
			break;
		}
			
	}
	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_RIGHT:
			printf("Released right arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_active, _OCT_position2D_stop, 0, 0);
		}
	}
}