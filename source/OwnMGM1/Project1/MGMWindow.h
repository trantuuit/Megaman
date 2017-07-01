#pragma once
#include<Windows.h>
#include"Config.h"
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

