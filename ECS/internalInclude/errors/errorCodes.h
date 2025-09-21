#pragma once

#define FATAL_THRESHOLD 9999

typedef enum {
	// memory
	EXIT_FAILED_TO_ALLOCATE		= 1000,
	

	// math
	ERR_DIVIDE_BY_ZERO			= 20000,

	// unsupported
	EXIT_3D_NOT_SUPPORTED		= 5030
} errorCodes;
