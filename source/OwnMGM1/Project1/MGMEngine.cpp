#include "MGMEngine.h"

MGMEngine* MGMEngine::instance = 0;
MGMEngine::MGMEngine()
{
	this->hWnd = MGMWindow::getInstance()->getHandleWindow();
	init();
}
MGMEngine* MGMEngine::getInstance()
{
	if (instance == 0)
		instance = new MGMEngine();
	return instance;
}
bool MGMEngine::isInitDirectX()
{
	LPDIRECT3D9 d3d;
	if (NULL == (d3d = Direct3DCreate9(D3D_SDK_VERSION)))
		return false;

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = BACKBUFFER_WIDTH;
	d3dpp.BackBufferHeight = BACKBUFFER_HEIGHT;

	if (FAILED(d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddv)))
	{
		return false;
	}
	if (!d3ddv)
		return false;
	d3d->Release();
	return true;
}
bool MGMEngine::isInitSprite()
{
	HRESULT hr = D3DXCreateSprite(d3ddv, &sprite);
	return !FAILED(hr);
}
bool MGMEngine::isSetBackBuffer()
{
	HRESULT hr = d3ddv->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
		&backBuffer);
	return !FAILED(hr);
}
bool MGMEngine::isSetFrameBuffer()
{

	HRESULT hr = d3ddv->CreateOffscreenPlainSurface(272,
		192,
		D3DFMT_X8R8G8B8,
		D3DPOOL_DEFAULT,
		&frameBuffer,
		0);
	return !FAILED(hr);
}
void MGMEngine::init()
{
	if (!isInitDirectX() || !isInitSprite() || !isSetBackBuffer() || !isSetFrameBuffer())
		errorMessage();
}
void MGMEngine::errorMessage()
{
	MessageBox(hWnd, "failed graphics", "Failed", MB_ICONERROR);
}
void MGMEngine::Release()
{
	if (d3ddv)
	{
		d3ddv->Release();
		d3ddv = 0;
	}
	if (frameBuffer)
	{
		frameBuffer->Release();
		frameBuffer = 0;
	}
	if (backBuffer)
	{
		backBuffer->Release();
		backBuffer = 0;

	}
	if (sprite)
	{
		sprite->Release();
		sprite = 0;
	}
}
LPDIRECT3DDEVICE9 MGMEngine::GetDevice()
{
	return d3ddv;
}

LPDIRECT3DSURFACE9 MGMEngine::GetBackBuffer()
{
	return backBuffer;
}

LPD3DXSPRITE MGMEngine::GetSprite()
{
	return sprite;
}
void MGMEngine::PrintText(char* str, int size, int x, int y, DWORD color)
{
	ID3DXFont* dxfont;
	RECT textbox;
	SetRect(&textbox, x, y, 272, 272);
	D3DXCreateFont(d3ddv,
		size, 
		0, 
		FW_NORMAL, 
		1, 
		false,
		DEFAULT_CHARSET, 
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,  
		DEFAULT_PITCH | FF_DONTCARE,
		"Arial",  
		&dxfont);  
	dxfont->DrawTextA(NULL,
		str,
		strlen(str),
		&textbox,
		DT_LEFT | DT_TOP,
		color);

	dxfont->Release();
}
void MGMEngine::BeginGraphics()
{
	HRESULT hr = d3ddv->BeginScene();
	HRESULT hr1 = sprite->Begin(D3DXSPRITE_ALPHABLEND);
	d3ddv->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(10, 10, 10), 1.0f, 0);
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBox(0, "Not start", "Failed", MB_ICONERROR);
		PostQuitMessage(0);
	}
}

void MGMEngine::EndGraphics()
{
	HRESULT hr1 = sprite->End();
	HRESULT hr = d3ddv->EndScene();
	if (FAILED(hr) || FAILED(hr1))
	{
		MessageBox(0, "Not end draw", "Failed", MB_ICONERROR);
		PostQuitMessage(0);
	}
}
void MGMEngine::PresentBackBuffer()
{
	d3ddv->Present(0, 0, 0, 0);
}
MGMEngine::~MGMEngine()
{
	Release();
}
