#include "myStandards.h"

#include "runtime/gameLoop.h"

static bool running = true;

void gameLoop(HWND windowHandle) {
	MSG messageID;

	while (running == true) {
		while (GetMessage(&messageID, NULL, 0, 0) > 0) {
			TranslateMessage(&messageID);
			DispatchMessage(&messageID);
		}
	}

	running = 0;
	SendMessage(windowHandle, WM_CLOSE, 0, 0);
}