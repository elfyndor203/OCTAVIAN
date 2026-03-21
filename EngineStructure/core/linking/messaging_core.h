#pragma once
#include "linking/types_core.h"

#include "OCT_Math.h"
#include <stdbool.h>

#include "layout/engineLayout.h"

#define cOCT_MESSAGES_MAX 64

enum cOCT_messageTypes {
	cOCT_MSG_ALLCLEAR,
	cOCT_MSG_TEXTURE_LOAD,
	cOCT_MSG_TEXTURE_DONE,

	cOCT_MSG_RENDERABLE_NEW
};

struct cOCT_message {
	cOCT_messageTypes messageType;

	union {
		struct { OCT_handle texHandle;  char* pixels; int width; int height; } texture_load;
		struct { OCT_handle texHandle; uint32_t rendererRef; } texture_done;

		struct { OCT_handle layerHandle; OCT_vec4 color; OCT_vec4 uv; OCT_handle entityHandle; OCT_handle transformHandle;} renderable_new;
	};
};

struct cOCT_messageBox {
	OCT_subsystemList owner;
	cOCT_message queue[cOCT_MESSAGES_MAX];
	OCT_counter count;
	OCT_counter head;
	OCT_counter tail;
};

bool cOCT_message_push(OCT_subsystemList recipient, cOCT_message message);
cOCT_message cOCT_message_pop(OCT_subsystemList self);