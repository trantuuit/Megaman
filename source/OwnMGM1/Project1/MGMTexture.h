#pragma once
#include<Windows.h>
#include<d3dx9.h>
#include"MGMPoint.h"
#include"MGMDirectXTool.h"

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
	MGMPoint anchorPoint;

	Direction imageDirection;

	MGMTexture(const char* filepath, D3DCOLOR transColor);
	////tao texture
	// filepath: duong dan file hinh anh
	// transColor: mau can trong suot
	MGMTexture(){}
	void Init(const char* filepath, D3DCOLOR transColor);

	////ham ve len backbuffer
	// x,y
	// r vung muon ve

	void RenderTexture(int x, int y, RECT *r);
	~MGMTexture();
};

