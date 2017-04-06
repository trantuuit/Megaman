#include"MGMCamera.h"
//#include "Megaman.h"
//#include"MGMSpriteManager.h"
//#include"KEY.h"
//#include<string>
//extern double jumpVolume;
//
//Megaman * Megaman::instance = 0;
//Megaman * Megaman::getInstance()
//{
//	if (instance == 0)
//		instance = new Megaman();
//	return instance;
//}
///*Cập nhật vận tốc */
//void Megaman::update()
//{
//	bool isKeyLeftDown = KEY::getInstance()->isLeftDown;
//	bool isKeyRightDown = KEY::getInstance()->isRightDown;
//	bool isKeyMoveDown = KEY::getInstance()->isMoveDown;
//	bool isKeyJumpPress = KEY::getInstance()->isJumpPress;
//	bool isKeyMovePress = KEY::getInstance()->isMovePress;
//	if (isKeyLeftDown)
//		objectDirection = LEFT;
//	if (isKeyRightDown)
//		objectDirection = RIGHT;
//
//	
//	//if (isKeyMovePress) curAction = 0;
//	if (isKeyMoveDown&&!isKeyMovePress)
//	{
//		vx = objectDirection*0.3;
//		if (isOnGround)
//		{
//			curAction = 2;
//		}
//	}
//	else
//	{
//		vx = 0;
//	}
//	if (isOnGround)
//	{
//		if (isKeyJumpPress)
//		{
//			vy = jumpVolume;
//			curAction = 3;
//			isOnGround = false;
//		}
//	}
//	//if (!isOnGround) curAction = 3;
//	if (vx == 0 && isOnGround) curAction = 0;
//	MGMMovableObject::update();
//	
//}
//
//void Megaman::render()
//{
//	MGMMovableObject::render();
//}
//
//void Megaman::onCollision(MGMBox * other, int nx, int ny)
//{
//	MGMMovableObject::onCollision(other, nx, ny);
//	isOnGround = ny;
//	/*if (ny == 1)
//	{
//		if (KEY::getInstance()->isJumpPress)
//		{
//			vy = jumpVolume;
//		}
//	}*/
//}
//
//Megaman::Megaman()
//{
//	sprite = MGMSpriteManager::getInstance()->sprites[SPR_MEGAMAN];
//	width = 10;
//	height = 24;
//	ax = 0;
//	isOnGround = 0;
//}
//
//
//Megaman::~Megaman()
//{
//}


//hung fix


#include "Megaman.h"
#include"MGMSpriteManager.h"
#include"KEY.h"
#include<string>
#include"MegamanBullet.h"


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
	//timeStand.update();
	//timeGo.update();
	//if (timeStand.isReady() && timeGo.isTerminated())
	//{
	//	timeStand.start();
	//}
	//if (timeGo.isReady() && timeStand.isTerminated())
	//{
	//	timeGo.start();
	//}
	//if (timeStand.isOnTime())
	//{
	//	setCurAction(MGM_STAND);
	//}
	//if (timeGo.isOnTime())
	//{
	//	setCurAction(MGM_RUN);
	//}

	//MGMMovableObject::update();

	//pauseAnimation = false;
	bool isKeyLeftDown = KEY::getInstance()->isLeftDown;
	bool isKeyRightDown = KEY::getInstance()->isRightDown;
	bool isKeyMoveDown = KEY::getInstance()->isMoveDown;
	bool isKeyJumpPress = KEY::getInstance()->isJumpPress;
	bool isKeyMovePress = KEY::getInstance()->isMovePress;
	bool isAttackPress = KEY::getInstance()->isAttackPress;

	if (isOnStairs)
	{
		isKeyMoveDown = false;
		isKeyLeftDown = false;
		isKeyRightDown = false;
		/*Megaman::getInstance()->setCurAction(MGM_CLIMB);*/
		/*if (KEY::getInstance()->isUpHold|| KEY::getInstance()->isDownHold)
		{
			setCurAction(MGM_CLIMB);
		}*/
	}
	if (isKeyLeftDown)
	{
		objectDirection = LEFT;
	}
	if (isKeyRightDown)
	{
		objectDirection = RIGHT;
	}

	if (isOnGround && isKeyJumpPress)
	{
		vy = MEGAMAN_VY_JUMP;
	}
	if (isKeyMoveDown)
	{
		setCurAction(MGM_PRE_RUN);
		vx = objectDirection*MEGAMAN_VX_GO;

	}
	else
	{
		vx = 0;
		if (!isOnStairs) setCurAction(MGM_STAND);
	}

	if (!isOnGround && !isOnStairs)
		setCurAction(MGM_JUMP);

	if (!delayShoot.isOnTime() && isOnGround && isAttackPress && MegamanBullet::getBullets()->Count<3)
	{
		MegamanBullet* bullet = new MegamanBullet();
		bullet->dx = 2 * objectDirection;
		bullet->x = x;
		bullet->y = y;
		delayShoot.start();
	}

	delayShoot.update();
	this->updateMove();
	updateFrameAnimation();
	isOnGround = false;


}

void Megaman::render()
{

	if (sprite == 0)
		return;
	float xDraw, yDraw;
	MGMCamera::getInstance()->Transform(x, y, xDraw, yDraw);
	//Nếu hướng object khác hướng hình vẽ( hướng hình vẽ = left(-1))

	int widthSprite = sprite->animations[curAction].frames[curFrame].width;
	if(curAction !=MGM_CLIMB)
		xDraw -= (widthSprite - width) / 2;

	if (objectDirection != sprite->pImage->imageDirection)
	{
		//Lật x bằng cách nhân tất cả điểm ảnh cho ma trận bên dưới
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			2 * (xDraw + widthSprite / 2), 0, 0, 1)));
	}



	this->sprite->Render(xDraw, yDraw, curAction, curFrame);

	if (objectDirection != sprite->pImage->imageDirection)
	{
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)));
	}
}

void Megaman::setCurAction(int action)
{

	if (this->action == MGM_RUN && action == MGM_PRE_RUN)
		return;
	this->action = action;
	if (action == MGM_CLIMB || action == MGM_JUMP)
		setWidth(15);
	else 
		setWidth(20);

	MGMMovableObject::setCurAction(action);
}

void Megaman::onInterserct(MGMBox * other)
{

	if (other->collisionCategory == CC_GROUND 
		&& this->getRight() > other->getLeft()
		&& this->getLeft()<other->getLeft()) 
		this->x = other->getLeft() - this->width-1;
}

void Megaman::onLastFrameAnimation(int action)
{
	bool isKeyMoveDown = KEY::getInstance()->isMoveDown;
	if (action == MGM_PRE_RUN && isKeyMoveDown)
	{
		setCurAction(MGM_RUN);
	}
}

void Megaman::updateFrameAnimation()
{
	if(!pauseAnimation)
		MGMMovableObject::updateFrameAnimation();
}

void Megaman::setWidth(int width)
{
	if (objectDirection == RIGHT)
	{
		x += this->width - width;
	}

	this->width = width;
}


void Megaman::onCollision(MGMBox * other, int nx, int ny)
{

	if (ny == 1)
	{
		isOnGround = true;
		isOnStairs = false;
	}
	MGMMovableObject::onCollision(other, nx, ny);
}

Megaman::Megaman()
{
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_MEGAMAN];
	width = 20;
	height = 23;
	ax = 0;
	delayShoot.init(300);
	isOnGround = false;
	isOnStairs = false;
	pauseAnimation = false;
	collisionCategory = CC_MEGAMAN;


}


Megaman::~Megaman()
{
}
