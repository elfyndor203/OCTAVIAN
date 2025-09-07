#include "messageHandler.h"

LRESULT CALLBACK windowProcedure(HWND windowHandle, UINT messageID, WPARAM wParam, LPARAM lParam) {

	switch (messageID) {
	case WM_CLOSE:
		DestroyWindow(windowHandle);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT: {
		PAINTSTRUCT paintbrush;
		HDC context = BeginPaint(windowHandle, &paintbrush);
		EndPaint(windowHandle, &paintbrush);

	}

	default:
		return gameMessageHandler(windowHandle, messageID, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK gameMessageHandler(HWND windowHandle, UINT messageID, WPARAM wParam, LPARAM lParam) {
	switch (messageID) {

	case WM_KEYDOWN:
		;
		gameObject* mainObject = createGameObject(2, componentPosition2D, componentHitBox2D);
		printComponentsList(mainObject);

		layer* myNewLayer = createNewLayer(true);
		//drawHitBox2D(mainObject->hitBox2D);

		break;

	default:
		return DefWindowProc(windowHandle, messageID, wParam, lParam);
	}
	return 0;
}