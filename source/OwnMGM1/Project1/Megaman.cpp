#include"MGMCamera.h"
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

	//@Tu-Đang đứng trên gạch và nhận sự kiện nhảy từ bán phím thì gán vận tốc vy = MEGAMAN_VY_JUMP
	if (isOnGround && isKeyJumpPress)
	{
		vy = MEGAMAN_VY_JUMP;
	}
	if (isKeyMoveDown) //@Tu_Nếu đang di chuyển thì thực hiện xét action chạy cho megaman đồng thời set vx cho nó
	{
		setCurAction(MGM_PRE_RUN);
		vx = objectDirection*MEGAMAN_VX_GO;

	}
	else //@Tu-Ngược lại set vx=0 đồng thời set action đứng cho megaman
	{
		vx = 0;
		if (!isOnStairs) 
			setCurAction(MGM_STAND);
	}
	//@Tu-Nếu không va chạm với gạch và không đứng trên cầu thanh thì chuyển hành động nhảy
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

/*
*@TranTu
*Override lại hàm updateFrameAnimation
*
*/
void Megaman::updateFrameAnimation()
{
	if (!pauseAnimation){
		if (sprite == 0)
			return;
		MGMBox::update();
		//updateMove();
		if (timeFrame.atTime()) {
			int lastFrame = curFrame;
			if (!curAction == MGM_STAND){
				this->sprite->Update(curAction, curFrame);
				if (lastFrame == this->sprite->animations[curAction].framesCount - 1 && curFrame == 0)
					onLastFrameAnimation(curAction);
			}
			else{
				if (!eyesTime1.isOnTime()){
					eyesTime1.start();

				}
				else{
					//Xử lý mở mắt
					this->sprite->Update(MGM_STAND, curFrame = 0);

				}
				if (!eyesTime2.isOnTime()){
					eyesTime2.start();

				}
				else{
					//Xử lý nhắm mắt
					this->sprite->Update(MGM_STAND, curFrame = 1);

				}
				eyesTime1.update();
				eyesTime2.update();
			}
		}
	}
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
	
	//@TranTu-khoi tao thoi gian nham mo mat 5 giay, nham mat 2 giay
	eyesTime1.init(5000);
	eyesTime2.init(2000);
	

}


Megaman::~Megaman()
{
}
