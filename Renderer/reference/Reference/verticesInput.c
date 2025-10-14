#include "Reference/verticesInput.h"

float TEST_VERTICES[] = {                    //actual points to be rendered
 0.0f,  0.75f, 0.0f,  // tip
 0.5f,  0.25f, 0.0f,  // tri base R
-0.5f,  0.25f, 0.0f,  // tri base L
 0.5f, -0.5f, 0.0f,  // bottom R
-0.5f, -0.5f, 0.0f,  // bottom L
};
unsigned int TEST_INDICES[] = {  // note that we start from 0!
    0, 1, 2, // roof
    1, 2, 3, // room rightx
    2, 3, 4  // room lefts
};