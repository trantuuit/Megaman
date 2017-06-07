#include "Met.h"
#include"Megaman.h"
#include"EnemyBullet.h"
#include"MegamanBullet.h"
#include"EffectCreateItem.h"
#include"MGMAudioManager.h"
Met::Met()
{
	vx = 0;
	vy = 0;
	ay = 0;
	timeAttack.init(1000);
	timeSleep.init(700);
	categoryEnemy = CREP_SCREW_BOMBER;
	CountShot = 0;
}


Met::~Met()
{
}

void Met::update()
{
	Megaman*mgm = Megaman::getInstance();
	if (x > mgm->x) objectDirection = LEFT;
	else if (x < mgm->x) objectDirection = RIGHT;


	if (abs(x - mgm->x) <= 85)
	{
		setCurAction(MET_ATTACK);
		if (timeAttack.isReady() && !timeSleep.isSchedule())
		{
			CountShot = 0;
			timeAttack.start();
		}

		if (timeSleep.isReady() && !timeAttack.isSchedule()) timeSleep.start();
		if (timeSleep.isSchedule()) setCurAction(MET_SLEEP);
		timeSleep.isFinish();
	}
	else if (!timeAttack.isSchedule()) setCurAction(MET_SLEEP);

	if (timeAttack.isSchedule())
	{
		setCurAction(MET_ATTACK);
		if (CountShot == 0) CreateBullet();
		CountShot++;
	}
	timeAttack.isFinish();



	timeAttack.update();
	timeSleep.update();
	//updateFrameAnimation();
}

void Met::CreateBullet()
{
	MGMAudioManager::getInstance()->Play(AUDIO_ENEMY_SHOOT);
	EnemyBullet *newBullet1 = new EnemyBullet();
	newBullet1->objectDirection = objectDirection;
	newBullet1->categoryBullet = FOR_MET;
	newBullet1->dx = 2 * objectDirection;
	newBullet1->dy = 0;
	newBullet1->x = this->x + 9;
	newBullet1->y = this->y - 4;

	EnemyBullet *newBullet2 = new EnemyBullet();
	newBullet2->objectDirection = objectDirection;
	newBullet2->categoryBullet = FOR_MET;
	newBullet2->dx = 2 * objectDirection;
	newBullet2->dy = 1;
	newBullet2->x = this->x + 9;
	newBullet2->y = this->y - 4;

	EnemyBullet *newBullet3 = new EnemyBullet();
	newBullet3->objectDirection = objectDirection;
	newBullet3->categoryBullet = FOR_MET;
	newBullet3->dx = 2 * objectDirection;
	newBullet3->dy = -1;
	newBullet3->x = this->x + 9;
	newBullet3->y = this->y - 4;

}
void Met::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET) {
		//count++;
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (this->curAction == MET_ATTACK) {
			count++;
			if (count == 1)
			{
				mgmbullet->x = this->x;
				mgmbullet->y = this->y;
				mgmbullet->setAction(FIRE);
				isKill = true;
				count = 0;
				Megaman::getInstance()->score += 500;
				EffectCreateItem::getInstance()->enemy = this;
				EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
			}
		}
		if (count != 1)
		{
			MGMAudioManager::getInstance()->Play(AUDIO_DINK);
			mgmbullet->setAction(NONE);
		}
	}
}
void  Met::onCollision(MGMBox * otherObject, int nx, int ny) {

}
