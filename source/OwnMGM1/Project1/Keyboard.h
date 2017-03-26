#pragma once

#include <dinput.h>
#ifndef KEYBOARD_H_
#define KEYBOARD_H_
#include<dinput.h>
class CKeyboard
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	LPDIRECTINPUT8       m_di;      
	LPDIRECTINPUTDEVICE8 m_keyboard;
	DIDEVICEOBJECTDATA m_keyEvents[1024];

	BYTE  m_keyStates[256];	
	CKeyboard(HINSTANCE hInstance, HWND hWnd);
	static CKeyboard* instance;
public:
	static CKeyboard* getInstance();
	static void Create(HINSTANCE hInstance, HWND hWnd);
	~CKeyboard();
	void UpdateKeyboard();
	void PollKeyboard();
	bool IsKeyDown(BYTE keyCode);
	bool IsKeyUp(BYTE keyCode);
	/*void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);*/
	void Release();
};

#endif

