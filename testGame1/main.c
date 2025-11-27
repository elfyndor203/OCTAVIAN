#include "main.h"

int main() {

	printf("hey \n");
	size_t rootObject = OCT_gameObject_createNew(0, false);
	OCT_hitBox2D_addNew(rootObject);

	size_t oneObjectHA = OCT_gameObject_createNew(0, false);
	OCT_position2D_addNew(oneObjectHA);
	OCT_hitBox2D_addNew(oneObjectHA);
	OCT_hitBox2D_resize(oneObjectHA, 55, 100);

	//printf("address of counter: %p\n", (void*)getHitBox2DCounter());
	//printf("value of counter: %zu\n", *getHitBox2DCounter());
}