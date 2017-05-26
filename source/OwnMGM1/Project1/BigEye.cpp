#include "BigEye.h"
#include "Megaman.h"
#include <stdlib.h>
#include <time.h>
#include "MegamanBullet.h"
#include"EffectCreateItem.h"

BigEye::BigEye()
{
	vx = -0.3;
	//vy = 0.85;
	ay = GRAVITY;
	activity = BIGEYE_STAND;
	delayBeforeJump.init(500);
	delayBeforeJump.start(500);
	categoryEnemy = CREP_BIG_EYE;
	count = 0;
}

void BigEye::onCollision(MGMBox * otherObject, int nx, int ny)
{
	if (ny == 1)
	{
		activity = BIGEYE_STAND;
		delayBeforeJump.start();
	}
	MGMMovableObject::onCollision(otherObject, nx, ny);
}
void BigEye::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		count++;
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (count == 2){

			mgmbullet->x = this->x+width/6;
			mgmbullet->y = this->y-height/6;
			mgmbullet->setAction(FIRE);
			isKill = true;
			count = 0;
			Megaman::getInstance()->score += 9000;
			EffectCreateItem::getInstance()->enemy = this;
			EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
		}
		else{
			mgmbullet->setAction(NONE);
		}
	}
}
void BigEye::update()
{
	switch (activity)
	{
	case BIGEYE_STAND:
		vx = 0;
		vy = 0;
		ay = 0;
		curFrame = 0;
		if (delayBeforeJump.isFinish())
		{
			objectDirection = (Megaman::getInstance()->getXCenter() < this->getXCenter()) ? LEFT : RIGHT;
			curFrame = 1;
			vx = 0.33 * objectDirection;
			vy = ramdomVy() == 0 ? 0.67 : 0.95;
			ay = GRAVITY;
			activity = BIGEYE_JUMP;
		}
		break;
	case BIGEYE_JUMP:
		break;
	default:
		break;
	}
	delayBeforeJump.update();

	MGMMovableObject::deltaUpdate();
	//MGMBox::update();
}

void BigEye::render()
{
	MGMEnemy::render();
}

int BigEye::ramdomVy()
{
	srand(time(NULL));
	int result = rand() % 2;
	return result;
}


BigEye::~BigEye()
{
}
