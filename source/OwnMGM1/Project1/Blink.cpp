#include "Blink.h"
#include "MGMSpriteManager.h"


Blink* Blink::instance = 0;
Blink * Blink::getInstance()
{
	if (instance == 0)
		instance = new Blink();
	return instance;
}

Blink::Blink()
{
	dx = 0;
	dy = 0;
	ax = 0;
	ay = 0;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_BLINK];
	renderFrameCount = 0;
	NotRenderFrameCount = 0;
	isRender = false;
}

void Blink::render()
{
	if (renderFrameCount < 5)
	{
		renderFrameCount++;
		//render
		MGMMovableObject::render();
		isRender = true;
	}
	else
	{
		NotRenderFrameCount++;
		// not render
		isRender = false;
	}
	if (NotRenderFrameCount >= 5)
	{
		renderFrameCount = 0;
		NotRenderFrameCount = 0;
	}

}



Blink::~Blink()
{
}
