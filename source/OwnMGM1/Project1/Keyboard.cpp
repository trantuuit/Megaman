#include "Keyboard.h"

CKeyboard* CKeyboard::instance = 0;

CKeyboard::CKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	m_hWnd = hWnd;
	m_hInstance = hInstance;
	DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8, (VOID**)&m_di, NULL		);
	m_di->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	m_keyboard->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE);

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024; 

	m_keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	m_keyboard->Acquire();

	for (int i = 0; i < 256; i++)
	{
		m_keyStates[i] = 0x00;
		m_keyBuffer[i] = false;
	}
}


CKeyboard * CKeyboard::getInstance()
{
	return instance;
}

void  CKeyboard::Create(HINSTANCE hInstance, HWND hWnd)
{
	instance = new CKeyboard(hInstance, hWnd);
}

CKeyboard::~CKeyboard()
{
	//Release();
}


void CKeyboard::PollKeyboard()
{
	m_keyboard->Poll();
	if (FAILED(m_keyboard->GetDeviceState(sizeof(m_keyEvents), (LPVOID)&m_keyEvents)))
	{
		//keyboard device lost, try to re-acquire
		m_keyboard->Acquire();
		m_keyboard->GetDeviceState(sizeof(m_keyEvents), (LPVOID)&m_keyEvents);
	}
	else
	{
		m_keyboard->GetDeviceState(sizeof(m_keyEvents), (LPVOID)&m_keyEvents);
	}

}

void CKeyboard::UpdateKeyboard()
{
	BYTE keys[256];
	m_keyboard->GetDeviceState(256, keys);
	for (int i = 0; i < 256; i++)
	{
		m_keyStates[i] = keys[i];
	}

	DWORD dwElements = 1024;
	HRESULT hr = m_keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), m_keyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = m_keyEvents[i].dwOfs;
		int KeyState = m_keyEvents[i].dwData;
		for (int j = 0; j < 256; j++)
		{
			m_keyBuffer[j] = false;
			if (KeyCode == j)
			{
				if ((KeyState & 0x80) > 0)
				{
				
					m_keyBuffer[j] = true;
				}
				else m_keyBuffer[j] = false;
			}
		}
		/*if ((KeyState & 0x80) > 0)
			OnKeyDown(KeyCode);
		else
			OnKeyUp(KeyCode);*/
	}
}
void CKeyboard::Release()
{
	if (m_keyboard )
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}
	if (m_di)
	{
		m_di->Release();
		m_di = 0;
	}
}
bool CKeyboard::IsKeyDown(BYTE keyCode)
{
	return (m_keyStates[keyCode] & 0x80) > 0;
}
bool CKeyboard::IsKeyPress(BYTE keyCode)
{
	return m_keyBuffer[keyCode];
}
bool CKeyboard::IsKeyUp(BYTE keyCode)
{
	return !((m_keyStates[keyCode] & 0x80) > 0);
}

