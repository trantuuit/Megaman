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
		if (isKeyJumpPress) {
			isOnStairs = false;
			pauseAnimation = false;
		}
			 // đang đứng trên cầu thang nhấn space sẽ rơi tự do xuống
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
		if (lastKeyDownRunAttack){
			if (delayAnimateRunShoot.isReady())
			{
				delayAnimateRunShoot.start();
			}
			
			if (delayAnimateRunShoot.isTerminated()){
				setCurAction(MGM_RUN);
				lastKeyDownRunAttack = false;
			}
			delayAnimateRunShoot.update();
		}
		else{
			setCurAction(MGM_PRE_RUN);
		}
		vx = objectDirection*MEGAMAN_VX_GO;
		lastKeyDownStandAttack = false;
	}
	else //@Tu-Ngược lại set vx=0 đồng thời set action đứng cho megaman
	{
		vx = 0;
		if (!isOnStairs) {
			if (lastKeyDownStandAttack){
				if (delayAnimateStandShoot.isReady())
				{
					delayAnimateStandShoot.start();
				}
				if (delayAnimateStandShoot.isTerminated()){
					setCurAction(MGM_STAND);
					lastKeyDownStandAttack = false;
				}
				delayAnimateStandShoot.update();
			}
			else{
				setCurAction(MGM_STAND);
			}
		}
	}
	//if (isOnGround && !isOnStairs){
	//	setCurAction(MGM_STAND);
	//}
	//@Tu-Nếu không va chạm với gạch và không đứng trên cầu thanh thì chuyển hành động nhảy
	if (!isOnGround && !isOnStairs){
		if (lastStatusJumpAttack){
			if (delayAnimateJumpShoot.isReady())
			{
				delayAnimateJumpShoot.start();
			}
			if (delayAnimateJumpShoot.isOnTime()){
				setCurAction(MGM_JUMP_ATTACK);
			}
			if (delayAnimateJumpShoot.isTerminated()){
				setCurAction(MGM_JUMP);
				lastStatusJumpAttack = false;
			}
			delayAnimateJumpShoot.update();
		}
		else{
			setCurAction(MGM_JUMP);
		}
	}

	if (!delayShoot.isOnTime() && isKeyMoveDown && isOnGround && isAttackPress && MegamanBullet::getBullets()->Count < 3){
		MegamanBullet* bullet = new MegamanBullet();
		bullet->dx = 4 * objectDirection;
		if (objectDirection == 1){
			bullet->x = x + 19;
		}
		else{
			bullet->x = x - 7;
		}

		bullet->y = y - 7;
		delayShoot.start();
		setCurAction(MGM_RUN_ATTACK);
		lastKeyDownRunAttack = true;
	}

	if (!delayShoot.isOnTime() && isOnGround && isAttackPress && MegamanBullet::getBullets()->Count<3)
	{
		
		MegamanBullet* bullet = new MegamanBullet();
		bullet->dx = 4 * objectDirection;
		if (objectDirection == 1){
			bullet->x = x + 19;
		}
		else{
			bullet->x = x - 7;
		}

		bullet->y = y - 8;
		delayShoot.start();
		setCurAction(MGM_STAND_ATTACK);
		lastKeyDownStandAttack = true;
	}

	if (!delayShoot.isOnTime() && !isOnGround && !isOnStairs && isAttackPress && MegamanBullet::getBullets()->Count < 3){
		MegamanBullet* bullet = new MegamanBullet();
		bullet->dx = 4 * objectDirection;
		if (objectDirection == 1){
			bullet->x = x + 17;
		}
		else{
			bullet->x = x - 7;
		}

		bullet->y = y - 8;
		delayShoot.start();
 		setCurAction(MGM_JUMP_ATTACK);
		lastStatusJumpAttack = true;
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
		if (timeFrame.atTime()) {
			int lastFrame = curFrame;
			if (curAction == MGM_STAND){
					this->sprite->Update(MGM_STAND, curFrame = 0);
					if (!eyesTime.isOnTime()){
						eyesTime.start();
					}
					else{
						//Xử lý nhắm mắt
						this->sprite->Update(MGM_STAND, curFrame = 1);
					}
					eyesTime.update();
				}
			else{
				this->sprite->Update(curAction, curFrame);
				if (lastFrame == this->sprite->animations[curAction].framesCount - 1 && curFrame == 0)
					onLastFrameAnimation(curAction);
			}
			//lastAction = curAction;
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
	delayShoot.init(150);
	isOnGround = false;
	isOnStairs = false;
	pauseAnimation = false;
	collisionCategory = CC_MEGAMAN;
	
	//@TranTu-khoi tao thoi gian nham mo mat 5 giay, nham mat 2 giay
	eyesTime.init(2000);
	/*eyesTime2.init(4000);*/
	timeFrame.tickPerFrame = 80;
	delayAnimateStandShoot.init(250);
	delayAnimateRunShoot.init(300);
	delayAnimateJumpShoot.init(200);
}


Megaman::~Megaman()
{
}
