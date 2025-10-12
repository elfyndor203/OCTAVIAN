#pragma once
#include "RendererStandards.h"
#include "RendererTypes.h"

rendererObjectIndex registerObject(size_t engineIndex, GLRequest VAORequest, GLRequest VBORequest, GLRequest EBORequest, bool is3D, bool dynamic);

