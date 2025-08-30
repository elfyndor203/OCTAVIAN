#include "position2D.h"

position2D* createDefaultPosition2D(gameObject* parent) {
	position2D* newPosition2D = mallocCheck(sizeof(position2D), "newPosition2D");


	newPosition2D->parent = parent;
	newPosition2D->globalPosition2D = originZeroZero; // sets the global position to 0,0
	newPosition2D->localPosition2D = originZeroZero; // sets the local position to 0,0

	return newPosition2D;
}