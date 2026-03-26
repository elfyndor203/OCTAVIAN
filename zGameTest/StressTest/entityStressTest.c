#include "arm.h"

#include "OCT_Math.h"
#include "OCT_EngineStructure.h"
#include "OCT_Errors.h"
#include "OCT_ECS.h"
#include "OCT_Renderer.h"
#include "OCT_Resources.h"
#include "OCT_window.h"
#include "OCT_Input.h"

#include "main.h"

#include <math.h>
#include <stdlib.h>

#define STRESS_ENTITY_COUNT 1250
#define STRESS_ARM_LENGTH 10

typedef struct {
    OCT_handle entity;
    OCT_vec2 velocity;
    float rotSpeed;
} stressEntity;

int main() {
    OCT_WDWModule_init("Stress Test", 1920, 1080, clearColor);
    OCT_RESModule_init();
    OCT_RENModule_init((OCT_vec2) { 960, 540 });
    OCT_ECSModule_init();

    OCT_handle contextRoot;
    OCT_handle context = OCT_entityContext_open(&contextRoot);

    OCT_handle tex1 = OCT_image_load("ztestFiles/hannes.png");
    OCT_handle tex2 = OCT_image_load("ztestFiles/anya.png");
    OCT_RENModule_flush();
    OCT_handle layer1 = OCT_layer_open(true, tex1);
    OCT_handle layer2 = OCT_layer_open(true, tex2);

    // spawn stress entities, each with a small arm cluster
    stressEntity entities[STRESS_ENTITY_COUNT];
    arm armList[STRESS_ENTITY_COUNT * 4];
    int armCount = 0;
    for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
        OCT_handle root = OCT_entity_new(context);
        entities[i].entity = root;

        // random starting position across virtual screen
        float x = ((float)rand() / RAND_MAX) * 900 - 450;
        float y = ((float)rand() / RAND_MAX) * 500 - 250;
        OCT_transform2D_moveBy(root, (OCT_vec2) { x, y });

        // random velocity
        entities[i].velocity.x = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        entities[i].velocity.y = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
        entities[i].rotSpeed = ((float)rand() / RAND_MAX) * 0.05f - 0.025f;

        // attach a small arm in each diagonal
        OCT_handle armRoot;
        OCT_handle layer = (i % 2 == 0) ? layer1 : layer2;
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { 1, 1 }, & armRoot);
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { 1, -1 }, & armRoot);
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { -1, 1 }, & armRoot);
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { -1, -1 }, & armRoot);
        printf("Armcount: %d\n", armCount);
    }

    float time = 0.0f;
    int frame = 0;

    while (!OCT_window_closed()) {
        OCT_WDWModule_startFrame();
        frame++;
        time += 0.016f;

        for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
            OCT_handle e = entities[i].entity;

            // move and bounce off virtual screen edges
            OCT_transform2D_moveBy(e, entities[i].velocity);
            OCT_vec2 pos = OCT_transform2D_readPosGlobal(e);
            if (pos.x > 480 || pos.x < -480) entities[i].velocity.x *= -1;
            if (pos.y > 270 || pos.y < -270) entities[i].velocity.y *= -1;

            // constant rotation
            OCT_transform2D_rotateByRad(e, entities[i].rotSpeed);
        }

        // hold space to curl all arms
        if (OCT_keyState_read(OCT_KEY_SPACE) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
                // rotate root entity faster to stress hierarchy propagation
                OCT_transform2D_rotateByRad(entities[i].entity, 0.05f);
            }
        }

        // rest positions
        if (OCT_keyState_read(OCT_KEY_R) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
                OCT_transform2D_moveTo(entities[i].entity, (OCT_vec2) { 0, 0 });
            }
        }

        if (OCT_keyState_read(OCT_KEY_LEFT) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < armCount; i++) {
                rotateArm(armList[i], 1, 1.1);
            }
        }

        if (OCT_keyState_read(OCT_KEY_RIGHT) == OCT_KEYSTATE_DOWN) {
            for (int i = 1; i < armCount; i++) {
                rotateArm(armList[i], -1, 1.1);
            }
        }

        if (OCT_keyState_read(OCT_KEY_2) == OCT_KEYSTATE_DOWN) {
            OCT_transform2D_scaleBy(contextRoot, (OCT_vec2) { 1.01, 1.01 });
        }
        if (OCT_keyState_read(OCT_KEY_1) == OCT_KEYSTATE_DOWN) {
            OCT_transform2D_scaleBy(contextRoot, (OCT_vec2) { 0.99, 0.99 });
        }

        OCT_INPModule_update();
        OCT_ECSModule_update();
        OCT_RENModule_update();
        OCT_WDWModule_endFrame();
    }
}