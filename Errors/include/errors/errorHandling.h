#pragma once
#include <stdbool.h>
#include "errorCodes.h"

bool logError(errorCodes errorCode);	// true if error, false if warning