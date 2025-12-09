#include "standards/rendererStandards_internal.h"
#include "OCT_EngineStructure.h"

void testKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_RIGHT:
			printf("Pressed right arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_ACTIVE, _OCT_position2D_move, 0.01);
		}
	}
	if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_RIGHT:
			printf("Released right arrow\n");
			_OCT_sendMessage(_OCT_ECS, _OCT_ACTIVE, _OCT_position2D_stop, 0);
		}
	}
}