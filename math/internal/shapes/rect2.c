#include "shapes/rect2.h"

OCT_rect2 OCT_rectangle2D_generate(OCT_vec2 center, OCT_vec2 dimensions, float rotation) {
    OCT_vec2 halfDimensions = { dimensions.x / 2.0f, dimensions.y / 2.0f };

    OCT_vec2 bottomLeft = { -halfDimensions.x, -halfDimensions.y };
    OCT_vec2 bottomRight = { halfDimensions.x, -halfDimensions.y };
    OCT_vec2 topRight = { halfDimensions.x, halfDimensions.y };
    OCT_vec2 topLeft = { -halfDimensions.x, halfDimensions.y };

    OCT_rect2 newBox;
    newBox.origin = center;
    newBox.dimensions = dimensions;
    newBox.rotation = rotation;

    newBox.bottomLeft = OCT_vec2_add(OCT_vec2_rotate(bottomLeft, rotation), center);
    newBox.bottomRight = OCT_vec2_add(OCT_vec2_rotate(bottomRight, rotation), center);
    newBox.topRight = OCT_vec2_add(OCT_vec2_rotate(topRight, rotation), center);
    newBox.topLeft = OCT_vec2_add(OCT_vec2_rotate(topLeft, rotation), center);

    //printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", newBox.bottomLeft.x, newBox.bottomLeft.y, newBox.bottomRight.x, newBox.bottomRight.y, newBox.topRight.x, newBox.topRight.y, newBox.topLeft.x, newBox.topLeft.y);
    return newBox;
}
