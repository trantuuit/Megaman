#pragma once
#include<Windows.h>
#include<d3dx9.h>
#include"MGMWindow.h"
class MGMEngine
{
public:
	MGMEngine();
	~MGMEngine();
	static MGMEngine* getInstance();
	LPDIRECT3DDEVICE9 d3ddv;
	LPDIRECT3DSURFACE9 frameBuffer;
	LPDIRECT3DSURFACE9 backBuffer;
	LPD3DXSPRITE sprite;
	HWND hWnd;
	static MGMEngine* instance;
	bool isInitDirectX();
	bool isInitSprite();
	bool isSetFrameBuffer();
	bool isSetBackBuffer();
	void init();
	void errorMessage();
	void Release();
	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DSURFACE9 GetBackBuffer();
	LPD3DXSPRITE GetSprite();
	void PrintText(char* str, int size, int x, int y, DWORD color);
	void BeginGraphics();
	void EndGraphics();
	void PresentBackBuffer();
};

