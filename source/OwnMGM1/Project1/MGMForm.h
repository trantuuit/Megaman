#pragma once
#include<Windows.h>
#include"Config.h"
class MGMForm
{
private:
	MGMForm(void);
	HWND hWnd;
	static MGMForm *instance;
public:
	static MGMForm *getInstance();
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	void initHandleWindows(HINSTANCE hInstance, int nCmdShow);
	HWND getHandleWindow();
	
	~MGMForm(void);
};

