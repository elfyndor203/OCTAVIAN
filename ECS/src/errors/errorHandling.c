#include "errors/errorHandling.h"

bool logError(errorCodes errorCode) {
	printf("Error: %d\n", errorCode);
	if (errorCode <= FATAL_THRESHOLD) {
		exit(errorCode);
	}
}