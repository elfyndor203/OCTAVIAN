#include "shapes/box2D_internal.h"

OCT_box2D OCT_box2D_generate(OCT_vertex2D center, OCT_vector2D dimensions, float rotation) {
    OCT_vector2D halfDimensions = { dimensions.x / 2.0f, dimensions.y / 2.0f };

    OCT_vector2D bottomLeft = { -halfDimensions.x, -halfDimensions.y };
    OCT_vector2D bottomRight = { halfDimensions.x, -halfDimensions.y };
    OCT_vector2D topRight = { halfDimensions.x, halfDimensions.y };
    OCT_vector2D topLeft = { -halfDimensions.x, halfDimensions.y };

    OCT_box2D newBox;
    newBox.origin = center;
    newBox.dimensions = dimensions;
    newBox.rotation = rotation;

    newBox.bottomLeft = OCT_vector2D_vector2D(OCT_OP_ADD, OCT_vector2D_rotate(bottomLeft, rotation), center);
    newBox.bottomRight = OCT_vector2D_vector2D(OCT_OP_ADD, OCT_vector2D_rotate(bottomRight, rotation), center);
    newBox.topRight = OCT_vector2D_vector2D(OCT_OP_ADD, OCT_vector2D_rotate(topRight, rotation), center);
    newBox.topLeft = OCT_vector2D_vector2D(OCT_OP_ADD, OCT_vector2D_rotate(topLeft, rotation), center);

    return newBox;
    printf("Generated vertices (%f, %f), (%f, %f), (%f, %f), (%f, %f)\n", newBox.bottomLeft.x, newBox.bottomLeft.y, newBox.bottomRight.x, newBox.bottomRight.y, newBox.topRight.x, newBox.topRight.y, newBox.topLeft.x, newBox.topLeft.y);
}
