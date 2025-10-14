#include "ECSStandards.h"

void* mallocCheck(size_t sizeToMalloc, const char* name) {
	void* pointer = malloc(sizeToMalloc);
	if (pointer == NULL) {
		fprintf(stderr, "Failed to allocate memory for %s", name);
		logError(EXIT_FAILED_TO_ALLOCATE);
	}
	return pointer;
}