#include "stairs.h"
#include"KeyCheck.h"
#include"Megaman.h"
#include"Collision.h"

stairs::stairs()
{

	collisionCategory = CC_STAIRS;
}


stairs::~stairs()
{
}

void stairs::onCollision(MGMBox * otherObject, int nx, int ny)
{
	/*bool isKeyUpHold = KeyCheck::getInstance()->isUpHold;
	if (otherObject->vx > 0 && otherObject->getRight() > this->getXCenter())
	{
		if (isKeyUpHold) otherObject->dy = 0.3;
	}
	else if (otherObject->vx < 0 && otherObject->getLeft() < this->getXCenter())
	{
		if (isKeyUpHold) otherObject->dy = 0.3;
	}*/
}

void stairs::climbStairs()
{
	Megaman *mgm = Megaman::getInstance();
	bool isKeyUpHold = KeyCheck::getInstance()->isUpHold;
	bool isKeyDownHold = KeyCheck::getInstance()->isDownHold;
	bool isAttackPress = KeyCheck::getInstance()->isAttackPress;

	//B1: neu truc trung tam cua cau thang nam giua hinh chu nhat doi tuong MGM lam tiep B2
	//B2: neu toa 
	if (!mgm->isOnStairs&&
		mgm->getRight() > this->getLeft() && mgm->getLeft() < this->getRight())
	{
		float nx, ny;
		float t = Collision::SweptAABB(mgm, this, nx, ny);
		if (ny == 1)
		{
			mgm->dy = -(mgm->getBottom() - this->getTop() - 1);
			mgm->isOnGround = true;
		}
	}
	if (mgm->getRight() > this->getXCenter() && mgm->getLeft() < this->getXCenter())
	{


		if (mgm->isOnStairs&& mgm->getBottom() == this->getTop() - 10)
		{
			//Collision::checkCollision(mgm, this);
			mgm->y = this->getTop() + mgm->height + 2;
			mgm->isOnGround = true;
			mgm->isOnStairs = false;
		}
		else if (mgm->isOnStairs&&mgm->getTop() == this->getBottom() + 5)
		{
			mgm->isOnStairs = false;
		}
		if ((isKeyUpHold && mgm->getBottom() >= this->getBottom() && mgm->getBottom() < this->getTop() - 1)
			|| (isKeyDownHold && mgm->getBottom() <= this->getTop() + 1 && mgm->getBottom() > this->getBottom()))
			mgm->isOnStairs = true;

		if (mgm->isOnStairs)
		{
			mgm->dx = 0;
			mgm->dy = 0;
			mgm->ay = 0;
			mgm->vy = -0.3f;
			mgm->x = this->x;
			if (mgm->getBottom() == this->getTop()) mgm->y = this->getTop() + 10;
		}
		else
		{
			mgm->ay = GRAVITY;

		}
		if (isKeyUpHold&&mgm->isOnStairs)
		{
			mgm->dy = 1;
		}
		else if (isKeyDownHold&&mgm->isOnStairs)
		{
			mgm->dy = -1;
		}

	}

	if (mgm->isOnStairs)
	{
		if (mgm->dy != 0)
		{
			if (Megaman::getInstance()->isChangeCutMan){
				Megaman::getInstance()->setCurAction(MGM_SKIN_CLIMB);
			}
			else{
				Megaman::getInstance()->setCurAction(MGM_CLIMB);
			}
			
			mgm->pauseAnimation = false;
		}
		/*else mgm->pauseAnimation = true;*/
	}


	if (mgm->isOnStairs)
	{
		if (KeyCheck::getInstance()->isAttackDown)
		{
			if (Megaman::getInstance()->isChangeCutMan){
				Megaman::getInstance()->setCurAction(MGM_SKIN_STAND_STAIR_ATTACK);
			}
			else{
				mgm->setCurAction(MGM_STAND_STAIR_ATTACK);
			}
			
		}
	}
}
