#include "OCT_EngineStructure.h"
#include "OCT_Math.h"
#include "OCT_Errors.h"
#include "OCT_ECS.h"
#include <inttypes.h>
#include "math.h"

#include "ECS/components/transform2D/transform2D_internal.h"
#include "ECS/entityContext/entityContext_internal.h"
#include "ECS/entity/entity_internal.h"
#include <Windows.h>
#include <stdio.h>

void entityConsole_open();
void renderEntityDashboard(iOCT_transform2D* array, int count);

int main() {
	OCT_startModule_ECS();
	entityConsole_open();

	OCT_entityHandle foreGround = OCT_entityContext_open();
	iOCT_entityContext* context = iOCT_entityContext_get(iOCT_entity_get(foreGround.entityContextID, foreGround.entityID)->entityContextID);
	iOCT_transform2D* transformArray = (iOCT_transform2D*)iOCT_pool_get(foreGround.entityContextID, OCT_typeComponentTransform2D)->array;

	OCT_entityHandle chara = OCT_entity_new(foreGround);
	OCT_hitBox2D_add(chara);
	OCT_entityHandle child = OCT_entity_new(chara);
	OCT_hitBox2D_add(child);
	OCT_entityHandle grandChild = OCT_entity_new(child);
	OCT_hitBox2D_add(grandChild);

	OCT_transform2D_moveBy(child, (OCT_vec2) { 1, 1 });
	OCT_transform2D_moveBy(grandChild, (OCT_vec2) { 2, 2 });
	// OCT_entityHandle grandChildHitBox2 = OCT_hitBox2D_add(grandChild);

	while (true) {
//		OCT_transform2D_moveBy(chara, (OCT_vec2){0.1f, 0.2f });
		OCT_transform2D_rotateByDeg(chara, 0.1f);
		//OCT_transform2D_moveBy(child, (OCT_vec2) { -0.1f, 0.2f });

		OCT_entityContext_update(foreGround);
		renderEntityDashboard(transformArray, 7);
//		Sleep(1);
	};

	OCT_entityContext_close(foreGround);
	return 0;
}

FILE* entityConsole;
void entityConsole_open() {
	AllocConsole();
	freopen_s(&entityConsole, "CONOUT$", "w", stdout);
	SetConsoleTitleA("Entity Debug");
}

void renderEntityDashboard(iOCT_transform2D* array, int count) {
	printf("\033[H"); // cursor to top-left

	for (int i = 0; i < count; i++) {
		iOCT_transform2D* t = &array[i];

		// Extract global TRS from global matrix
		float gx = t->globalMatrix.r0c2;
		float gy = t->globalMatrix.r1c2;

		float gScaleX = sqrtf(
			t->globalMatrix.r0c0 * t->globalMatrix.r0c0 +
			t->globalMatrix.r1c0 * t->globalMatrix.r1c0
		);

		float gScaleY = sqrtf(
			t->globalMatrix.r0c1 * t->globalMatrix.r0c1 +
			t->globalMatrix.r1c1 * t->globalMatrix.r1c1
		);

		float gRotation = atan2f(
			t->globalMatrix.r1c0,
			t->globalMatrix.r0c0
		);

		printf(
			"E%2" PRIu64 " T%2" PRIu64
			" | GPos = (% 8.2f,% 8.2f)"
			" GRot =% 7.2f"
			" GScale = (%.2f,%.2f)\n",
			t->entityID,
			t->transformID,
			gx,
			gy,
			OCT_rad2deg(gRotation),
			gScaleX,
			gScaleY
		);
	}

	fflush(stdout);
}

//void renderEntityDashboard(iOCT_transform2D* array, int count) {
//	// Move cursor to top-left
//	printf("\033[H"); // ANSI escape sequence for cursor home
//	for (int i = 0; i < count; i++) {
//		printf("Entity %2" PRIu64 " Transform %2" PRIu64 " | Pos = (% 9.2f, % 9.2f) | Rot = % 8.2f | Scale = (% .2f, % .2f)\n",
//			array[i].entityID,
//			array[i].transformID,
//			array[i].position.x,
//			array[i].position.y,
//			OCT_rad2deg(array[i].rotation),
//			array[i].scale.x,
//			array[i].scale.y
//		);
//	}
//	fflush(stdout);
//}