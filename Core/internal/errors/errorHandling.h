#pragma once
#include "errorCodes.h"

#include <stdbool.h>
#include <stdio.h>

bool logError(errorCodes errorCode);	// true if error, false if warning