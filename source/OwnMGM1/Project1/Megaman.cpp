#include "Megaman.h"
#include"MGMSpriteManager.h"
#include"KEY.h"
#include<string>
extern double jumpVolume;

Megaman * Megaman::instance = 0;
Megaman * Megaman::getInstance()
{
	if (instance == 0)
		instance = new Megaman();
	return instance;
}
/*Cập nhật vận tốc */
void Megaman::update()
{
	bool isKeyLeftDown = KEY::getInstance()->isLeftDown;
	bool isKeyRightDown = KEY::getInstance()->isRightDown;
	bool isKeyMoveDown = KEY::getInstance()->isMoveDown;
	bool isKeyJumpPress = KEY::getInstance()->isJumpPress;
	if (isKeyLeftDown)
		objectDirection = LEFT;
	if (isKeyRightDown)
		objectDirection = RIGHT;

	if (isKeyMoveDown)
	{
		vx = objectDirection*0.5;
		if (isOnGround) curAction = 2;
	}
	else
	{
		vx = 0;
	}
	if (isOnGround)
	{
		if (isKeyJumpPress)
		{
			vy = jumpVolume;
			curAction = 3;
			isOnGround = false;
		}
	}
	if (vx == 0 && isOnGround) curAction = 0;

	MGMMovableObject::update();
}

void Megaman::render()
{
	MGMMovableObject::render();
}

void Megaman::onCollision(MGMBox * other, int nx, int ny)
{
	MGMMovableObject::onCollision(other, nx, ny);
	isOnGround = ny;
	/*if (ny == 1)
	{
		if (KEY::getInstance()->isJumpPress)
		{
			vy = jumpVolume;
		}
	}*/
}

Megaman::Megaman()
{
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_MEGAMAN];
	width = 10;
	height = 24;
	ax = 0;
	isOnGround = 0;
}


Megaman::~Megaman()
{
}
