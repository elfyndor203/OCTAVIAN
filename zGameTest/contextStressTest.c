#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_ECS.h"
#include "OCT_Renderer.h"
#include "OCT_Resources.h"
#include "OCT_window.h"
#include "OCT_Input.h"

#include "arm.h"
#include "math.h"
#include "main.h"

#include <math.h>
#include <stdlib.h>

#define CONTEXT_COUNT     30
#define ENTITIES_PER_CONTEXT 6
#define ARM_LENGTH        10

typedef struct {
    OCT_handle context;
    OCT_handle root;
    OCT_handle entity;
    OCT_vec2 velocity;
    float rotSpeed;
} stressContext;

int contextmain() {
    OCT_WDWModule_init("Context Stress", 1920, 1080, clearColor);
    OCT_RESModule_init();
    OCT_RENModule_init((OCT_vec2) { 960, 540 });
    OCT_ECSModule_init();

    OCT_handle tex1 = OCT_image_load("ztestFiles/hannes.png");
    OCT_handle tex2 = OCT_image_load("ztestFiles/anya.png");
    OCT_RENModule_flush();
    OCT_handle layer1 = OCT_layer_open(true, tex1);
    OCT_handle layer2 = OCT_layer_open(true, tex2);

    stressContext contexts[CONTEXT_COUNT];

    for (int i = 0; i < CONTEXT_COUNT; i++) {
        OCT_handle contextRoot;
        contexts[i].context = OCT_entityContext_open(&contextRoot);
        contexts[i].root = contextRoot;

        // spawn a small cluster of entities in each context
        OCT_handle parent = contexts[i].context;
        for (int j = 0; j < ENTITIES_PER_CONTEXT; j++) {
            OCT_handle e = OCT_entity_new(parent);
            if (j == 0) contexts[i].entity = e;
            OCT_handle layer = (i % 2 == 0) ? layer1 : layer2;
            OCT_handle armRoot;
            spawnArm(ARM_LENGTH, e, layer, smallRect, (OCT_vec2) { 1, 1 }, & armRoot);
            spawnArm(ARM_LENGTH, e, layer, smallRect, (OCT_vec2) { 1, -1 }, & armRoot);
            spawnArm(ARM_LENGTH, e, layer, smallRect, (OCT_vec2) { -1, 1 }, & armRoot);
            spawnArm(ARM_LENGTH, e, layer, smallRect, (OCT_vec2) { -1, -1 }, & armRoot);
            parent = e;
        }

        // scatter across screen
        float x = ((float)rand() / RAND_MAX) * 900 - 450;
        float y = ((float)rand() / RAND_MAX) * 500 - 250;
        OCT_transform2D_moveBy(contexts[i].entity, (OCT_vec2) { x, y });

        contexts[i].velocity.x = ((float)rand() / RAND_MAX) * 1.5f - 0.75f;
        contexts[i].velocity.y = ((float)rand() / RAND_MAX) * 1.5f - 0.75f;
        contexts[i].rotSpeed = ((float)rand() / RAND_MAX) * 0.04f - 0.02f;
    }

    while (!OCT_window_closed()) {
        OCT_WDWModule_startFrame();

        for (int i = 0; i < CONTEXT_COUNT; i++) {
            OCT_handle e = contexts[i].entity;

            OCT_transform2D_moveBy(e, contexts[i].velocity);
            OCT_vec2 pos = OCT_transform2D_readPos(e);
            if (pos.x > 480 || pos.x < -480) contexts[i].velocity.x *= -1;
            if (pos.y > 270 || pos.y < -270) contexts[i].velocity.y *= -1;

            OCT_transform2D_rotateByRad(e, contexts[i].rotSpeed);
        }

        if (OCT_keyState_read(OCT_KEY_SPACE) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < CONTEXT_COUNT; i++) {
                OCT_transform2D_rotateByRad(contexts[i].entity, 0.05f);
            }
        }

        if (OCT_keyState_read(OCT_KEY_R) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < CONTEXT_COUNT; i++) {
                OCT_transform2D_moveTo(contexts[i].entity, (OCT_vec2) { 0, 0 });
            }
        }

        OCT_INPModule_update();
        OCT_ECSModule_update();
        OCT_RENModule_update();
        OCT_WDWModule_endFrame();
    }
}