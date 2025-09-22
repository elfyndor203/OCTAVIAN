#include "zzzTestMain.h"

int main() {

	printf("hey \n");
	size_t rootObject = gameObjectCreateNew(0, false);
	hitBox2DAddNew(rootObject);

	size_t oneObjectHA = gameObjectCreateNew(0, false);
	position2DAddNew(oneObjectHA);
	hitBox2DAddNew(oneObjectHA);
	hitBox2DResize(oneObjectHA, 55, 100);

	//printf("address of counter: %p\n", (void*)getHitBox2DCounter());
	//printf("value of counter: %zu\n", *getHitBox2DCounter());
}