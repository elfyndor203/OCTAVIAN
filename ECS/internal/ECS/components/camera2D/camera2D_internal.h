#include "ECS/types_internal.h"

#include "cOCT_EngineStructure.h"
#include "OCT_Math.h"

struct iOCT_camera2D {
	OCT_ID cameraID;
	OCT_ID parentID;

	OCT_vec2 position;
	float zoom;
	float rotation; 
};

iOCT_camera2D* iOCT_camera2D_get(iOCT_entityContext* context, OCT_ID cameraID);
OCT_ID iOCT_camera2D_add(iOCT_entityContext* context, OCT_ID entityID, OCT_vec2 position, float zoom, float rotation);
float iOCT_camera2D_zoom(iOCT_entityContext* context, OCT_ID cameraID, float delta);