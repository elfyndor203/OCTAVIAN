#include "OCT_EngineStructure.h"
#include "OCT_Math.h"
#include "OCT_Errors.h"
#include "OCT_ECS.h"

int main() {
	OCT_startModule_ECS();
	OCT_entityHandle foreGround = OCT_entityContext_open();

	OCT_entityHandle chara = OCT_entity_new(foreGround);
	OCT_hitBox2D_add(chara);
	OCT_entityHandle child = OCT_entity_new(chara);
	OCT_hitBox2D_add(child);
	OCT_entityHandle grandChild = OCT_entity_new(child);
	OCT_hitBox2D_add(grandChild);
	OCT_entityHandle grandChildHitBox2 = OCT_hitBox2D_add(grandChild);
	while (true) {
		OCT_transform2D_moveBy(grandChildHitBox2, (OCT_vec2){0.1f, 0.2f });
	};
	return 0;
}