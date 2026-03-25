#pragma once

typedef enum {
	OCT_ECStype_Entity,

	OCT_ECSType_transform2D,
	OCT_ECSType_hitBox2D,
	OCT_ECSType_sprite2D,
	OCT_ECSType_physics2D,

	OCT_ECSTypes_total
} OCT_ECSTypes; // IF UPDATED, ENTITYCONTEXT.c MUST ALSO BE UPDATED TO GET THE STRUCT SIZE