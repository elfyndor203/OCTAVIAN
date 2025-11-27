#pragma once

typedef enum {
	// memory
	EXIT_FAILED_TO_ALLOCATE = 1000,

	// math
	ERR_DIVIDE_BY_ZERO = 20000,
	ERR_VECTOR_FAILED = 20010,

	// ECS
	WARNING_COMPONENT_REPLACED = 300060,

	// unsupported
	EXIT_3D_NOT_SUPPORTED = 5030
} errorCodes;