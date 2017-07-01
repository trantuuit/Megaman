#pragma once
#include<Windows.h>
#include<d3dx9.h>
#include"MGMEngine.h"

enum Direction
{
	LEFT = -1,
	RIGHT = 1
};

class MGMTexture
{
private:
	LPDIRECT3DTEXTURE9 m_image;
public:
	int Width, Height;
	Direction imageDirection;
	MGMTexture(const char* filepath, D3DCOLOR transColor);
	MGMTexture();
	void Init(const char* filepath, D3DCOLOR transColor);
	void RenderTexture(int x, int y, RECT *r);
	~MGMTexture();
};

