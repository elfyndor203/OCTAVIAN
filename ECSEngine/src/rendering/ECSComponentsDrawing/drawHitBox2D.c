#include "drawHitBox2D.h"

myRGB hitBox2DBottomColor = { 255, 74, 54 }; // RED
myRGB hitBox2DRightColor = { 0, 234, 255 }; // CYAN
myRGB hitBox2DTopColor = { 119, 0, 255 }; // PURPLE
myRGB hitBox2DLeftColor = { 202, 3, 252 }; // PINK

void drawHitBox2D(hitBox2D* hitBox2DToDraw, layer* layer) {
	// bottom starts from origin
	vector2D rightPositionVector2D = addVectors2D(2, hitBox2DToDraw->origin, hitBox2DToDraw->bottom);
	vector2D topPositionVector2D = addVectors2D(2, rightPositionVector2D, hitBox2DToDraw->top);
	vector2D leftPositionVector2D = addVectors2D(2, topPositionVector2D, hitBox2DToDraw->left);

	line bottom = { hitBox2DToDraw->origin, hitBox2DToDraw->bottom, HITBOX2D_LINE_WIDTH, hitBox2DBottomColor };
	line right = { rightPositionVector2D, hitBox2DToDraw->right, HITBOX2D_LINE_WIDTH, hitBox2DRightColor};
	line top = { topPositionVector2D, hitBox2DToDraw->top, HITBOX2D_LINE_WIDTH, hitBox2DTopColor };
	line left = { leftPositionVector2D, hitBox2DToDraw->left, HITBOX2D_LINE_WIDTH, hitBox2DLeftColor };

	drawLineToLayer(&bottom, layer);
	drawLineToLayer(&right, layer);
	drawLineToLayer(&top, layer);
	drawLineToLayer(&left, layer);
}