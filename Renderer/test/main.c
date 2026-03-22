#include "cOCT_EngineStructure.h"
#include "OCT_Resources.h"
#include "OCT_window.h"
#include "OCT_ECS.h"
#include "OCT_Renderer.h"
#include "_ECS_Output/_REN_include.h"

#include "renderer/texture/texture_internal.h"

int main() {
	OCT_WDWModule_init("OTTO OCTAvian", 2000, 1000, black);
	OCT_RESModule_init();
	OCT_RENModule_init();
	OCT_ECSModule_init();

	OCT_vec4 solid = { 1.0, 1.0, 1.0, 1.0 };

	OCT_handle mainContextRoot;
	OCT_handle mainContext = OCT_entityContext_open(&mainContextRoot);

	OCT_handle mainTex = OCT_image_load("C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/Resources/internal/test/dark.png");
	OCT_RENModule_flush();
	OCT_handle layer = OCT_layer_open(true, mainTex);

	OCT_handle center = OCT_entity_new(mainContext);
	OCT_handle LB = OCT_entity_new(center);
	OCT_handle LT = OCT_entity_new(center);
	OCT_handle RT = OCT_entity_new(center);
	OCT_handle RB = OCT_entity_new(center);

	OCT_sprite2D_add(LB, layer, solid, (OCT_vec4) { 0.0, 0.0, 0.5, 0.5 });
	OCT_sprite2D_add(LT, layer, solid, (OCT_vec4) { 0.0, 0.5, 0.5, 0.5 });
	OCT_sprite2D_add(RT, layer, solid, (OCT_vec4) { 0.5, 0.5, 0.5, 0.5 });
	OCT_sprite2D_add(RB, layer, solid, (OCT_vec4) { 0.5, 0.0, 0.5, 0.5 });
	
	OCT_transform2D_scaleBy(mainContextRoot, (OCT_vec2) {0.7, 0.7});
	OCT_transform2D_scaleBy(center, (OCT_vec2) { 0.7, 0.7 });

	OCT_transform2D_moveBy(LB, (OCT_vec2) { -0.6, -0.6 });
	OCT_transform2D_moveBy(LT, (OCT_vec2) { -0.6, 0.6 });
	OCT_transform2D_moveBy(RT, (OCT_vec2) { 0.6, 0.6 });
	OCT_transform2D_moveBy(RB, (OCT_vec2) { 0.6, -0.6 });
	
	while (true) {
		OCT_window_wipe();

		//OCT_transform2D_rotateByDeg(newEntity, 1);
		//OCT_transform2D_rotateByDeg(child, 1);

		OCT_ECSModule_update();
		OCT_RENModule_update();
		OCT_window_show();
	};
	return 0;
}