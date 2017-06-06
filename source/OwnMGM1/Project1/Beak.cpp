#include "Beak.h"
#include "MegamanBullet.h"
#include"EffectCreateItem.h"
#include"MGMAudioManager.h"
void Beak::update()
{
	//@Tu-Add
	//chuyen huong cho trai sang phai cho enemy
	if (id == 106){
		this->objectDirection = Direction::RIGHT;
	}
	//---
	/*if (!isKill)*/{
		switch (beakActivity)
		{
		case BEAK_OPEN:
			if (delayActivity.isFinish())
			{
				pauseAnimation = false;
				setCurAction(0);
			}
			break;
		case BEAK_CLOSE:
			if (delayActivity.isFinish())
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
		if (beakActivity == BEAK_CLOSE && delayActivity.isSchedule())
		{
			if (!delayShoot.isSchedule())
			{
				delayShoot.start();
				EnemyBullet *newBullet = new EnemyBullet();
				newBullet->categoryBullet = FOR_BEAK;
				newBullet->objectDirection = objectDirection;
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
				MGMAudioManager::getInstance()->Play(AUDIO_ENEMY_SHOOT);
				//@Tu-add
				if (this->id == 106){
					newBullet->x = this->x + 9;
					newBullet->y = this->y - 5;
				}
				else{
					newBullet->x = this->x - 3;
					newBullet->y = this->y - 5;
				}
				//-----
			}
			delayShoot.update();
		}
	}

	if (!pauseAnimation)
		MGMObject::updateFrameAnimation();
}

void Beak::render()
{
	MGMEnemy::render();
}

void Beak::onCollision(MGMBox * otherObject, int nx, int ny)
{
}
void Beak::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (beakActivity == BEAK_CLOSE){
			mgmbullet->x = this->x;
			mgmbullet->y = this->y;
			mgmbullet->setAction(FIRE);
			isKill = true;
			Megaman::getInstance()->score += 200;
			EffectCreateItem::getInstance()->enemy = this;
			EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
		}
		else{
			MGMAudioManager::getInstance()->Play(AUDIO_DINK);
			mgmbullet->setAction(NONE);
		}

	}
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
	categoryEnemy = CREP_BEAK;
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
