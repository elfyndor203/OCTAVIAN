//
//Course Number : ENGR 13300
//Semester : Fall 2025
//Description :
//	Simple game mechanics with ECS-style logging and rendering
//
//	Assignment Information :
//Assignment:     Individual Project
//Team ID : LC4 - 11 
//Author : Elvin Li, li5423@purdue.edu
//Date : 12/09/2025
//
//Contributors:
//	https://learnopengl.com
//
//My contributor(s) helped me :
//[] understand the assignment expectations without
//telling me how they will approach it.
//[x] understand different ways to think about a solution
//without helping me plan my solution.
//[x] think through the meaning of a specific error or
//bug present in my code without looking at my code.
//Note that if you helped somebody else with their code, you
//have to list that person as a contributor here as well.
//
//Academic Integrity Statement :
//I have not used source code obtained from any unauthorized
//source, either modified or unmodified; nor have I provided
//another student access to my code.The project I am
//submitting is my own original work.
//

#include "main.h"

running = true;

int main() {
	OCT_window_initialize("Test Game Module", 1080, 1080);
	OCT_initializeShaders();

	OCT_entitySetID mainSet = OCT_entitySet_new();
	OCT_layerID newLayer = OCT_layer_new();

	OCT_entityHandle mainRoot = OCT_entitySet_root(mainSet);

	OCT_entityHandle testObject = OCT_entity_new(mainRoot);
	OCT_hitBox2D_addNew(testObject, newLayer);
	//OCT_hitBox2D_resize(testObject, 15.0, 15.0);
	OCT_entityHandle otherObject = OCT_entity_new(mainRoot);
	OCT_position2D_move(otherObject, 0.2, -0.3);
	OCT_hitBox2D_addNew(otherObject, newLayer);
	OCT_entityHandle childObject = OCT_entity_new(testObject);
	OCT_hitBox2D_addNew(childObject, newLayer);

	OCT_entityHandle noHitBox = OCT_entity_new(childObject);
	OCT_hitBox2D_resize(noHitBox, 3, 2);

	test_entitySetActive(childObject);
	float size = 1;

	int entityCount = 3;
	OCT_entityHandle entityList[3] = { testObject, otherObject, childObject };
	while (running) {
		OCT_handleRendererMessages();
		OCT_handleECSMessages();
		//OCT_transform2D_rotate(mainRoot, 1);		//NOTE_TRANSFORM_PROPAGATION

		//OCT_position2D_move(testObject, 0.0001, 0.002);
		OCT_transform2D_rotate(testObject, 1);
		OCT_transform2D_rotate(otherObject, 3);
		OCT_transform2D_rotate(childObject, -1);

		for (int i = 0; i < entityCount; i++) {
			OCT_render(entityList[i], OCT_typeComponentHitBox2D);
		}

		OCT_window_update();
		OCT_window_handleInputs();
	}
	return 0;
}