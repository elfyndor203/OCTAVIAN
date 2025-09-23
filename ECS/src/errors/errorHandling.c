#include "errors/errorHandling.h"

bool logError(errorCodes errorCode) {
	if (errorCode <= ERROR_THRESHOLD) {
		printf("Error: %d\n", errorCode);
		if (errorCode <= FATAL_THRESHOLD) {
			exit(errorCode);
		}
		return true;
	}

	else if (errorCode <= WARNING_THRESHOLD) {
		printf("Warning: %d\n", errorCode);
		return false;
	}
}