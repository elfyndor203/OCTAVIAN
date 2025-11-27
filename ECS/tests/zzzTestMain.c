#include "zzzTestMain.h"

int main() {

	printf("hey \n");
	size_t rootObject = gameObject_createNew(0, false);
	hitBox2D_addNew(rootObject);

	size_t oneObjectHA = gameObject_createNew(0, false);
	position2D_addNew(oneObjectHA);
	hitBox2D_addNew(oneObjectHA);
	hitBox2D_resize(oneObjectHA, 55, 100);

	//printf("address of counter: %p\n", (void*)getHitBox2DCounter());
	//printf("value of counter: %zu\n", *getHitBox2DCounter());
}