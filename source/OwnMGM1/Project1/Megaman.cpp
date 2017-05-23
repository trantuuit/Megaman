#include"MGMCamera.h"
#include "Megaman.h"
#include"MGMSpriteManager.h"
#include"KEY.h"
#include<string>
#include"MegamanBullet.h"
#include"MGMEnemy.h"
#include "MGMItem.h"
#include <stdlib.h>
#include <time.h>
#include "EnemyBullet.h"
#include "BoardBar.h"

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
	bool isKeyLeftDown, isKeyRightDown, isKeyMoveDown, isKeyJumpPress, isKeyMovePress, isAttackPress;
	isKeyLeftDown = isKeyRightDown = isKeyMoveDown = isKeyJumpPress = isKeyMovePress = isAttackPress = false;
	//Nhận các sự kiện từ bàn phím
	isKeyLeftDown = KEY::getInstance()->isLeftDown;
	isKeyRightDown = KEY::getInstance()->isRightDown;
	isKeyMoveDown = KEY::getInstance()->isMoveDown;
	isKeyJumpPress = KEY::getInstance()->isJumpPress;
	isKeyMovePress = KEY::getInstance()->isMovePress;
	isAttackPress = KEY::getInstance()->isAttackPress;
	if (isKeyLeftDown)
	{
		objectDirection = LEFT;
	}
	if (isKeyRightDown)
	{
		objectDirection = RIGHT;
	}

	//Xử lý tình huống trên cầu thang
	if (isOnStairs)
	{
		isKeyMoveDown = false;
		//đang đứng trên cầu thang nhấn space sẽ rơi tự do xuống
		if (isKeyJumpPress) {
			isOnStairs = false;
			pauseAnimation = false;
		}
		if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
			MegamanBullet* bullet = new MegamanBullet();
			bullet->dx = 4 * objectDirection;
			if (objectDirection == RIGHT){
				bullet->x = x + 17;
			}
			else{
				bullet->x = x - 7;
			}
			bullet->y = y - 8;
			delayShoot.start();
			setCurAction(MGM_STAND_STAIR_ATTACK);
			lastStatusStandStairAttack = true;
			pauseAnimation = false;
		}
		if (lastStatusStandStairAttack){
			if (delayAnimateStandStairShoot.isReady())
			{
				delayAnimateStandStairShoot.start();
			}
			if (delayAnimateStandStairShoot.isSchedule()){
				pauseAnimation = false;
				setCurAction(MGM_STAND_STAIR_ATTACK);
			}
			if (delayAnimateStandStairShoot.isFinish()){
				setCurAction(MGM_CLIMB);
				lastStatusStandStairAttack = false;
			}
			delayAnimateStandStairShoot.update();
		}
	}
	else if (isOnGround){
		if (isKeyJumpPress){
			vy = MEGAMAN_VY_JUMP;
		}
		if (isKeyMoveDown){
			if (lastStatusRunAttack){
				if (delayAnimateRunShoot.isReady())
				{
					delayAnimateRunShoot.start();
				}

				if (delayAnimateRunShoot.isFinish()){
					setCurAction(MGM_RUN);
					lastStatusRunAttack = false;
				}
				delayAnimateRunShoot.update();
			}
			else{
				setCurAction(MGM_PRE_RUN);
			}
			vx = objectDirection*MEGAMAN_VX_GO;
			lastStatusStandAttack = false;

			if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
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
				lastStatusRunAttack = true;
			}
		}
		else{
			vx = 0;
			if (lastStatusStandAttack){
				if (delayAnimateStandShoot.isReady()){
					delayAnimateStandShoot.start();
				}
				if (delayAnimateStandShoot.isFinish()){
					setCurAction(MGM_STAND);
					lastStatusStandAttack = false;
				}
				if (delayAnimateStandShoot.isSchedule()){
					setCurAction(MGM_STAND_ATTACK);
				}
				delayAnimateStandShoot.update();
			}
			else{
				setCurAction(MGM_STAND);
			}
			if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3)
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
				lastStatusStandAttack = true;
			}
		}
	}
	if (!isOnGround && !isOnStairs){
		if (lastStatusJumpAttack){
			if (delayAnimateJumpShoot.isReady())
			{
				delayAnimateJumpShoot.start();
			}
			if (delayAnimateJumpShoot.isSchedule()){
				setCurAction(MGM_JUMP_ATTACK);
			}
			if (delayAnimateJumpShoot.isFinish()){
				setCurAction(MGM_JUMP);
				lastStatusJumpAttack = false;
			}
			delayAnimateJumpShoot.update();
		}
		else{
			setCurAction(MGM_JUMP);
		}
		if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
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
		if (isKeyMoveDown){
			vx = objectDirection*MEGAMAN_VX_GO;
		}
	}
	//if (beingAttacked){
	//	setCurAction(9);
	//	curFrame = 0;
	//	vx = -0.5;
	//	beingAttacked = false;
	//}
	pauseAnimation = false;
	delayShoot.update();
	deltaUpdate();
	updateFrameAnimation();
	isOnGround = false;
}
void Megaman::deltaUpdate(){
	vx = vx + ax * GAMETIME;
	dx = vx * GAMETIME;

	vy = vy + ay * GAMETIME;
	dy = vy * GAMETIME;
}

void Megaman::render()
{
	if (sprite == 0)
		return;
	float xDraw, yDraw;
	MGMCamera::getInstance()->Transform(x, y, xDraw, yDraw);
	//Nếu hướng object khác hướng hình vẽ( hướng hình vẽ = left(-1))

	int widthSprite = sprite->animations[curAction].frames[curFrame].width;
	if (curAction != MGM_CLIMB)
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
	if (action == MGM_CLIMB || action == MGM_JUMP || action == MGM_STAND_STAIR_ATTACK)
		setWidth(16);
	else
		setWidth(20);

	MGMMovableObject::setCurAction(action);
}

void Megaman::onIntersectRect(MGMBox * otherObject)
{
	if (otherObject->collisionCategory == CC_ITEM){
		MGMItem* item = (MGMItem*)otherObject;
		srand(time(NULL));

		if (item->categoryItem == CI_LIFE_ENERGY_BIG){
			int result = rand() % 3 + 8;
			healthPoint += result;
		}
		if (item->categoryItem == CI_LIFE_ENERGY_SMALL){
			int result = rand() % 3 + 2;
			healthPoint += result;
		}
		if (item->categoryItem == CI_UP){
			life++;
		}
	}
	if (healthPoint > 28){
		healthPoint = 28;
	}
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
	if (!pauseAnimation){
		if (sprite == 0)
			return;
		if (timeFrame.atTime()) {
			int lastFrame = curFrame;
			if (curAction == MGM_STAND){
				//Xu ly mo mat
				this->sprite->Update(MGM_STAND, curFrame = 0);
				if (!eyesTime.isSchedule()){
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
			/*this->sprite->Update(curAction, curFrame);*/
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

void Megaman::onCollision(MGMBox * otherObject, int nx, int ny)
{
	if (ny == 1)
	{
		isOnGround = true;
		isOnStairs = false;
	}
	MGMMovableObject::onCollision(otherObject, nx, ny);
	if (otherObject->collisionCategory == CC_ENEMY){
		beingAttacked = true;
		MGMEnemy* enemy = (MGMEnemy*)otherObject;
		if (enemy->categoryEnemy == CREP_BLADER){
			healthPoint -= 3;
		}
		if (enemy->categoryEnemy == CREP_BEAK){
			healthPoint--;
		}
		if (enemy->categoryEnemy == CREP_OCTOPUS_BATTERY){
			healthPoint -= 4;
		}
		if (enemy->categoryEnemy == CREP_BIG_EYE){
			healthPoint -= 10;
		}
		if (enemy->categoryEnemy == CREP_FLYING_SHELL){
			healthPoint -= 1;
		}
		if (enemy->categoryEnemy == CREP_FLEA){
			healthPoint -= 2;
		}
		if (enemy->categoryEnemy == CREP_SCREW_BOMBER){
			healthPoint -= 1;
		}
		if (enemy->categoryEnemy == CREP_SUPER_CUTTER){
			healthPoint -= 4;
		}

	}
	if (otherObject->collisionCategory == CC_ENEMY_BULLET){
		beingAttacked = true;
		EnemyBullet* bullet = (EnemyBullet*)otherObject;
		if (bullet->categoryBullet == FOR_BEAK){
			healthPoint -= 1;
		}
		if (bullet->categoryBullet == FOR_FLYING_SHELL){
			healthPoint -= 2;
		}
		if (bullet->categoryBullet == FOR_SCREW_BOMBER){
			healthPoint -= 2;
		}
	}
	if (healthPoint < 0){
		healthPoint = 0;
	}
}

Megaman::Megaman()
{

	sprite = MGMSpriteManager::getInstance()->sprites[SPR_MEGAMAN];
	beingAttacked = false;
	score = 0;
	life = 2;
	healthPoint = 28;
	width = 20;
	height = 23;
	ax = 0;
	delayShoot.init(150);
	isOnGround = false;
	isOnStairs = false;
	pauseAnimation = false;
	collisionCategory = CC_MEGAMAN;
	IntersectDoor = -1;

	//@TranTu-khoi tao thoi gian nham mo mat 5 giay, nham mat 2 giay
	eyesTime.init(2000);
	/*eyesTime2.init(4000);*/
	timeFrame.tickPerFrame = 80;
	delayAnimateStandShoot.init(250);
	delayAnimateRunShoot.init(300);
	delayAnimateJumpShoot.init(200);
	delayAnimateStandStairShoot.init(200);
}


Megaman::~Megaman()
{
}
