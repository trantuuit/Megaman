#pragma once
#include<Windows.h>
#define FPS 160
#define TITLE_STR "Megaman"
#define MGMWindow_CLASS_NAME "MegamanForm"  
#define FORM_WIDTH 800
#define FORM_HEIGHT 600

#define BACKBUFFER_WIDTH 256
#define BACKBUFFER_HEIGHT 224

#define CAMERA_WIDTH 350
#define CAMERA_HEIGHT 350


class MGMWindow
{
private:
	MGMWindow(void);
	HWND hWnd;
	static MGMWindow *instance;
public:
	static MGMWindow *getInstance();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void initHandleWindows(HINSTANCE hInstance, int nCmdShow);
	HWND getHandleWindow();
	
	~MGMWindow(void);
};

