#pragma once

#include <Windows.h>
#include "myStandards.h"

#include "vectors.h"
#include "drawing.h"
#include "gameObjects.h"

LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT messageID, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK gameMessageHandler(HWND windowHandle, UINT messageID, WPARAM wParam, LPARAM lParam);