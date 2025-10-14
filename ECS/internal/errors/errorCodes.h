#pragma once

#define FATAL_THRESHOLD 9999
#define ERROR_THRESHOLD 99999
#define WARNING_THRESHOLD 999999

typedef enum {
	// memory
	EXIT_FAILED_TO_ALLOCATE		= 1000,
	
	// math
	ERR_DIVIDE_BY_ZERO			= 20000,

	// ECS
	WARNING_COMPONENT_REPLACED	= 300060,

	// unsupported
	EXIT_3D_NOT_SUPPORTED		= 5030
} errorCodes;
