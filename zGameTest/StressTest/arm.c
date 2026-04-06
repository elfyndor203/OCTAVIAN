#include "arm.h"
#include "definitions.h"

#include "OCT_engine.h"

#include <stdlib.h>

arm spawnArm(int count, OCT_handle context, OCT_handle layer, OCT_vec2 dimensions, OCT_vec2 direction, OCT_handle* outRoot) {
	arm newArm = { 0 };
	newArm.segmentList = malloc(count * sizeof(OCT_handle));
	newArm.segmentCount = count;

	OCT_handle nextParent = context;
	OCT_handle entity;
	OCT_vec2 currentDim = dimensions;
	for (int i = 0; i < count; i++) {
		entity = OCT_entity_new(nextParent);
		OCT_sprite2D_add(entity, layer, solidColor, (OCT_vec4) { 0.0, 0.0, 1.0, 1.0 }, currentDim);
		if (i > 0) {
			OCT_transform2D_moveBy(entity, OCT_vec2_mul(OCT_vec2_mul_eleWise(direction, currentDim), 0.9));
		}

		newArm.segmentList[i] = entity;
		nextParent = entity;
		currentDim = OCT_vec2_mul(currentDim, 0.9);
	}
	
	*outRoot = newArm.segmentList[0];
	return newArm;
}

void rotateArm(arm myArm, float rotation, float curlFactor) {
	OCT_handle segment;
	float curl = 1;
	for (int i = 0; i < myArm.segmentCount; i++) {
		segment = myArm.segmentList[i];
		OCT_transform2D_rotateByDeg(segment, rotation * curl);
		
		curl *= curlFactor;
	}
}

void scaleArm(arm myArm, OCT_vec2 scale) {
	OCT_handle segment;
	for (int i = 0; i < myArm.segmentCount; i++) {
		segment = myArm.segmentList[i];
		OCT_transform2D_scaleBy(segment, scale);
	}
}