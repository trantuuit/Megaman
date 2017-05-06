#include "Door.h"
#include "MGMSpriteManager.h"
#include"Megaman.h"
#include"MGMCamera.h"


Door::Door()
{
	collisionCategory = CC_DOOR;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_DOOR];
	objectDirection = LEFT;
}

void Door::Open()
{
	updateFrameAnimation();
}

void Door::Close()
{
	curAction =1;
	pauseAnimation = false;
	updateFrameAnimation();
}
void Door::updateFrameAnimation()
{
	if (sprite == 0)
		return;

	if (timeFrame.atTime())
	{
		if (!pauseAnimation)
		{
			this->sprite->Update(curAction, curFrame);
		}
	}
	if (curFrame == this->sprite->animations[curAction].framesCount - 1)
		onLastFrameAnimation(curAction);
}
void Door::onLastFrameAnimation(int curAction)
{
	if (curAction == 0)
	{
		Megaman::getInstance()->x += Megaman::getInstance()->objectDirection * 1;
		//Megaman::getInstance()->setCurAction(MGM_RUN);
		if (Megaman::getInstance()->curAction == MGM_PRE_RUN) Megaman::getInstance()->setCurAction(MGM_RUN);
		Megaman::getInstance()->updateFrameAnimation();
		MGMCamera::getInstance()->x += Megaman::getInstance()->objectDirection * 4;
	}
	if (curAction == 1)
	{
		isClosed = true;
	}
	pauseAnimation = true;
}

Door::Door(int x, int y, int w, int h)
{
	pauseAnimation = false;
	objectDirection = LEFT;
	collisionCategory = CC_DOOR;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_DOOR];
	this->x = x;
	this->y = y;
	this->width = w;
	this->height = h;
}


Door::~Door()
{
}
