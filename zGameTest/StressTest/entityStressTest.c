#include "arm.h"

#include "OCT_engine.h"

#include "main.h"

#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define STRESS_ENTITY_COUNT 2500
#define STRESS_ARM_LENGTH 10

OCT_vec4 color_black = { 0.0, 0.0, 0.0, 0.5 };

int main() {
    OCT_engine_start("OCTAVIAN", 1920, 1080, color_black, 960, 540, 240, 120, 60);

    OCT_handle contextRoot;
    OCT_handle context = OCT_entityContext_open(&contextRoot);

    OCT_handle tex1 = OCT_image_load("images/hannes.png");
    OCT_handle tex2 = OCT_image_load("images/anya.png");
    OCT_RENModule_flush();
    OCT_handle layer1 = OCT_layer_open(true, tex1);
    OCT_handle layer2 = OCT_layer_open(true, tex2);

    // spawn stress entities, each with a small arm cluster
    OCT_handle* entities = malloc(sizeof(OCT_handle) * STRESS_ENTITY_COUNT);;
    arm* armList = malloc(sizeof(arm) * STRESS_ENTITY_COUNT * 4);
    assert(entities && armList);

    int armCount = 0;
    for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
        OCT_handle root = OCT_entity_new(context);
        OCT_physics2D_add(root, root, 0.01, 3, 3, 3, 0.8);

        entities[i] = root;

        // random starting position across virtual screen
        float x = ((float)rand() / RAND_MAX) * 900 - 450;
        float y = ((float)rand() / RAND_MAX) * 500 - 250;
        OCT_transform2D_moveBy(root, (OCT_vec2) { x, y });

        // attach a small arm in each diagonal
        OCT_handle armRoot;
        OCT_handle layer = (i % 2 == 0) ? layer1 : layer2;
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { 1, 1 }, & armRoot);
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { 1, -1 }, & armRoot);
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { -1, 1 }, & armRoot);
        armList[armCount++] = spawnArm(STRESS_ARM_LENGTH, root, layer, smallRect, (OCT_vec2) { -1, -1 }, & armRoot);
        printf("Armcount: %d\n", armCount);
    }

    double time = 0.0;
    int frame = 0;

    while (!OCT_window_closed()) {
        OCT_WDWModule_startFrame();
        OCT_PLTModule_update();

        frame++;
        time += OCT_timer_getDeltaTime();
        printf("Frame: %d   Time: %lf MS\n", frame, time);

        // hold space to curl all arms
        if (OCT_keyState_read(OCT_KEY_SPACE) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
                // rotate root entity faster to stress hierarchy propagation
                OCT_transform2D_rotateByRad(entities[i], 0.05f);
            }
        }

        // rest positions
        if (OCT_keyState_read(OCT_KEY_R) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
                OCT_transform2D_moveTo(entities[i], (OCT_vec2) { 0, 0 });
            }
        }

        if (OCT_keyState_read(OCT_KEY_LEFT) == OCT_KEYSTATE_DOWN) {
            for (int i = 0; i < STRESS_ENTITY_COUNT; i++) {
                OCT_physics2D_addVelocity(entities[i], (OCT_vec2) { -0.1, 0});
            }
        }

        if (OCT_keyState_read(OCT_KEY_RIGHT) == OCT_KEYSTATE_DOWN) {
            for (int i = 1; i < STRESS_ENTITY_COUNT; i++) {
                OCT_physics2D_addVelocity(entities[i], (OCT_vec2) { 0.1, 0 });
            }
        }

        if (OCT_keyState_read(OCT_KEY_2) == OCT_KEYSTATE_DOWN) {
            OCT_transform2D_scaleBy(contextRoot, (OCT_vec2) { 1.01, 1.01 });
        }
        if (OCT_keyState_read(OCT_KEY_1) == OCT_KEYSTATE_DOWN) {
            OCT_transform2D_scaleBy(contextRoot, (OCT_vec2) { 0.99, 0.99 });
        }

        OCT_engine_tick();
    }

    OCT_engine_stop();
}