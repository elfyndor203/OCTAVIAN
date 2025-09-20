#include "zzzTestMain.h"

int main() {
	printf("hey \n");
	gameObject rootObject = createGameObject(0, false);

	position2DAddNew(rootObject.poolIndex);
	printf("%zu \n", getPosition2D(rootObject.poolIndex)->parentIndex);
	printf("hitbox: %zu \n", hitBox2DAddNew(rootObject.poolIndex));
	hitBox2DGenerateVertices(rootObject.poolIndex);

	gameObject childObject = createGameObject(rootObject.poolIndex, false);
	position2DAddNew(childObject.poolIndex);
	hitBox2DAddNew(childObject.poolIndex);
	printf("parent of child: %zu \n", getPosition2D(childObject.poolIndex)->parentIndex);
	printf("child hitbox: %zu \n", getHitBox2D(childObject.poolIndex)->poolIndex);
	hitBox2DGenerateVertices(childObject.poolIndex);

	printf("hitBox poolIndex=%zu bottomLeft=(%f,%f)\n",
		getHitBox2D(childObject.poolIndex)->poolIndex, getHitBox2D(rootObject.poolIndex)->bottomLeft.x, getHitBox2D(rootObject.poolIndex)->bottomLeft.y);

	printf("\n\nchild bottom left: (%f, %f)\n", getHitBox2D(childObject.poolIndex)->bottomLeft.x, getHitBox2D(childObject.poolIndex)->bottomLeft.y);

	hitBox2D* h1 = getHitBox2D(childObject.poolIndex);
	hitBox2D* h2 = &currentScene->hitBox2DPool[currentScene->gameObjectsPool[childObject.poolIndex].hitBoxIndex];
	printf("%p %p\n", (void*)h1, (void*)h2); // should be the same
	printf("%f %f\n", h1->bottomLeft.x, h1->bottomLeft.y);
}