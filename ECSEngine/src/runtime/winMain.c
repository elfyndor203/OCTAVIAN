#include "runtime/winMain.h"

const char windowClassName[] = "myWindowClass";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// create console
	AllocConsole();
	FILE* consoleFile;
	freopen_s(&consoleFile, "CONOUT$", "w", stdout);  // redirect stdout to console
	freopen_s(&consoleFile, "CONOUT$", "w", stderr);  // redirect stderr to console
	// create console

	//REGISTER THE WINDOW
	WNDCLASSEX windowClass;
	HWND windowHandle;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = 0;
	windowClass.lpfnWndProc = windowProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = windowClassName;
	windowClass.hbrBackground = CreateSolidBrush(RGB(37, 115, 85));
	windowClass.hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
	windowClass.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);

	if (!RegisterClassEx(&windowClass)) {
		MessageBox(NULL, "Window Class Registration Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
	}
	else {
		printf("Window Registered!\n");
	}
	// REGISTER THE WINDOW

	// CREATE THE WINDOW
	windowHandle = CreateWindowEx(WS_EX_CLIENTEDGE, windowClassName, "MyWindow", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080, NULL, NULL, hInstance, NULL);

	if (windowHandle == NULL) {
		MessageBox(NULL, "Window Creation Failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	else {
		printf("Window Created!\n");
	}

	ShowWindow(windowHandle, nCmdShow);
	//CREATE THE WINDOW

	UpdateWindow(windowHandle);

	gameLoop(windowHandle);

}


