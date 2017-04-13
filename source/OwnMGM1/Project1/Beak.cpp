﻿#include "Beak.h"



void Beak::update()
{
	if ((this->x == 833 && this->y==544) || (this->x==881 && this->y==752)){
		this->objectDirection = Direction::RIGHT;
	}
	switch (beakActivity)
	{
	case BEAK_OPEN:
		if (delayActivity.isTerminated())
		{
			pauseAnimation = false;
			setCurAction(0);
		}
		break;
	case BEAK_CLOSE:
		if (delayActivity.isTerminated())
		{
			pauseAnimation = false;
			setCurAction(1);
		}
		break;
	default:
		break;
	}
	delayActivity.update();

	// Delay giữa 2 viên đạn
	if (beakActivity == BEAK_CLOSE && delayActivity.isOnTime())
	{
		if (!delayShoot.isOnTime())
		{
			delayShoot.start();
			BeakBullet *newBullet = new BeakBullet();
			switch (bulletType)
			{
			case BULLET_1:
				newBullet->dx = 3 * objectDirection;
				newBullet->dy = 2;
				bulletType = BULLET_2;
				break;
			case BULLET_2:
				newBullet->dx = 3 * objectDirection;
				newBullet->dy = 1;
				bulletType = BULLET_3;
				break;
			case BULLET_3:
				newBullet->dx = 3 * objectDirection;
				newBullet->dy = -1;
				bulletType = BULLET_4;
				break;
			case BULLET_4:
				newBullet->dx = 3 * objectDirection;
				newBullet->dy = -2;
				bulletType = BULLET_1;
				break;
			default:
				break;
			}
			newBullet->x = this->x - 3;
			newBullet->y = this->y - 5;
		}
		delayShoot.update();
	}


	if (!pauseAnimation)
		MGMObject::updateFrameAnimation();

	//------------------------------------------------------------------------------------------------------------------
	// Update tọa độ các viên đạn:
	for (List<BeakBullet*>::Node *p = BeakBullet::getBullets()->pHead; p; p = p->pNext)
	{
		BeakBullet *_bullet = p->m_value;
		_bullet->updateLocation();
	}

	// Xóa các viên đạn không nằm trong Camera:
	for (int i = 0; i < BeakBullet::getBullets()->Count; i++)
	{
		BeakBullet* bullet = BeakBullet::getBullets()->at(i);
		if (!Collision::AABBCheck(bullet, MGMCamera::getInstance()))
		{
			BeakBullet::getBullets()->_Remove(bullet);
			delete bullet;
			i--;
		}
	}
}

void Beak::render()
{
	MGMEnemy::render();

	for (List<BeakBullet*>::Node *p = BeakBullet::getBullets()->pHead; p; p = p->pNext)
	{
		BeakBullet *_bullet = p->m_value;
		_bullet->render();
	}
}

void Beak::onCollision(MGMBox * other, int nx, int ny)
{
	MGMEnemy::onCollision(other, nx, ny);
	if (other->collisionCategory == CC_GROUND)
	{
		if (nx != 0)
			vx = (abs)(vx)* nx;
	}
	if (other->collisionCategory == CC_MEGAMAN)
		Collision::preventMove(Megaman::getInstance(), this);
}

//Override lại hàm:
void Beak::onLastFrameAnimation(int action)
{
	switch (beakActivity)
	{
	case BEAK_OPEN:
		beakActivity = BEAK_CLOSE;
		pauseAnimation = true;
		delayActivity.start(2000);
		curFrame = 3;
		break;
	case BEAK_CLOSE:
		beakActivity = BEAK_OPEN;
		pauseAnimation = true;
		delayActivity.start(1000);
		curFrame = 3;
		break;
	default:
		break;
	}
}

Beak::Beak()
{
	bulletType = BULLET_1;
	objectDirection = LEFT;
	curAction = 0;
	curFrame = 0;
	vx = 0;
	ax = 0;

	beakActivity = BEAK_ACTIVITY::BEAK_OPEN;
	pauseAnimation = true;
	delayActivity.start(2000);
	curFrame = 0;

	timeFrame = 100;
	delayShoot.init(500);
}


Beak::~Beak()
{
}