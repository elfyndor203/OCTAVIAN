#pragma once

typedef enum {
	OCT_typeEntity,

	OCT_typeComponentTransform2D,
	OCT_typeComponentHitBox2D,

	OCT_typesTotal
} OCT_types; // IF UPDATED, ENTITYCONTEXT.c MUST ALSO BE UPDATED TO GET THE STRUCT SIZE