#include "ECS.h"

int main() {
	gameObjectIndex testCharacter = gameObjectCreateNew(0, false);
	position2DAddNew(testCharacter);
	hitBox2DAddNew(testCharacter);
	hitBox2DResize(testCharacter, 100, 394);
	hitBox2DGenerateVertices(testCharacter);
}