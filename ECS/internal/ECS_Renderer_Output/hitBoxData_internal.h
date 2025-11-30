#pragma once
#include "ECS_Renderer_Output/hitBoxData.h"
#include "standards/ECSStandards_internal.h"

#include "ECS/components/hitBox2D/hitBox2D_internal.h"

#include <string.h>

#define HITBOX2D_OUTPUT_VERTEX_COUNT 4
#define HITBOX2D_OUTPUT_INDEX_COUNT 6

float hitBox2DVertexBuffer[HITBOX2D_OUTPUT_VERTEX_COUNT * 2];
int hitBox2DIndexBuffer[HITBOX2D_OUTPUT_INDEX_COUNT];

size_t* iREN_hitBox2DVertices_getCount();
size_t* iREN_hitBox2DIndices_getCount();

float* iREN_hitBox2DVertices_get(iOCT_sceneID sceneID, iOCT_componentID engineLink);
unsigned int* iREN_hitBox2DIndices_get();
