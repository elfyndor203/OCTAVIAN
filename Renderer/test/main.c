#include "cOCT_EngineStructure.h"
#include "iOCT_Resources.h"
#include "OCT_window.h"
#include "OCT_ECS.h"
#include "_ECS_Output/_REN_include.h"
#include "renderer/layer/layer_internal.h"
#include "renderer/module/rendererModule_internal.h"
#include "renderer/rendererObject/rendererObject.h"
#include "renderer/shader/shader/shader.h"
#include "renderer/spriteData/spriteData_internal.h"

#include "renderer/texture/texture_internal.h"

int main() {
	OCT_WDWModule_init("OTTO OCTAvian", 3000, 2000);
	iOCT_RENModule_init();
	iOCT_RESModule_init();
	OCT_ECSModule_init();


	OCT_image gear = iOCT_image_loadPNG("C:/Users/Elfyndor/MyDocuments/Projects/OCTAVIAN/Resources/internal/test/dark.png");
	GLuint texture = iOCT_texture2D_load(gear.pixels, gear.width, gear.height);
	
	OCT_ID newLayer = iOCT_layer_open(true, texture);
	iOCT_layer* layerPt = iOCT_layer_get(newLayer);

	OCT_handle root;
	OCT_handle context = OCT_entityContext_open(&root);
	OCT_handle entity = OCT_entity_new(context);
	OCT_handle transform = _tOCT_transform2D_getHandleFromEntity(entity);

	OCT_transform2D_moveBy(entity, (OCT_vec2) { 0.2, 0.2 });

	OCT_handle renObj = iOCT_rendererObject_add(layerPt, entity, transform);

	while (true) {
		OCT_entityContext_update(context);

		OCT_window_wipe();
		iOCT_layer_draw(layerPt);
		OCT_window_show();
	};
	return 0;
}