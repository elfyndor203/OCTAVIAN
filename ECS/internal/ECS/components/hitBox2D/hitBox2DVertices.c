#include "ECS/components/hitBox2D/hitBox2DVertices_internal.h"
#include "ECS/scene/scene_internal.h"

OCT_subcomponentID hitBox2D_generateVertices(OCT_gameObjectID parentIndex) {
	hitBox2D* hitBox = hitBox2D_get(parentIndex);
	vector2D hitBoxWidth = { hitBox->size.x, 0 };
	vector2D hitBoxHeight = { 0, hitBox->size.y };
	vector2D totalOffset = OCT_vector2D_Vector2D(OCT_OP_ADD, hitBox->localOrigin, position2D_get(parentIndex)->globalPosition2D);

	vertex2D bottomLeft = OCT_vector2D_Vector2DMulti(OCT_OP_ADD, 3, totalOffset, hitBox->localOrigin, OCT_vector2D_Scalar(OCT_OP_DIVIDE, hitBox->size, -2.0f));
	vertex2D bottomRight = OCT_vector2D_Vector2D(OCT_OP_ADD, bottomLeft, hitBoxWidth);
	vertex2D topRight = OCT_vector2D_Vector2D(OCT_OP_ADD, bottomRight, hitBoxHeight);
	vertex2D topLeft = OCT_vector2D_Vector2D(OCT_OP_ADD, topRight, OCT_vector2D_Scalar(OCT_OP_MULTIPLY, hitBoxHeight, -1));

	printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y, topRight.x, topRight.y, topLeft.x, topLeft.y);

	hitBox2DVertices newHitBoxVertices = {
		*hitBox2D_getCounter(),
		hitBox->poolIndex,
		hitBox->localOrigin,
		bottomLeft,
		bottomRight,
		topRight,
		topLeft
	};

	newHitBoxVertices.poolIndex = *hitBox2DVertices_getCounter();
	newHitBoxVertices.hitBoxIndex = hitBox->poolIndex;
	hitBox->verticesIndex = newHitBoxVertices.poolIndex;
	hitBox2DVertices_getPool()[*hitBox2DVertices_getCounter()] = newHitBoxVertices;
	*hitBox2DVertices_getCounter() += 1;
	return newHitBoxVertices.poolIndex;
}