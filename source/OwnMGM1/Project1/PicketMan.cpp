#include "PicketMan.h"
#include"Megaman.h"
#include"Collision.h"
#include"PKMWeapon.h"
#include<ctime>
#include"EffectCreateItem.h"
#include"Megaman.h"
#include"MegamanBullet.h"
#include"MGMAudioManager.h"
void PicketMan::update()
{
	srand(time(0));
	Megaman*mgm = Megaman::getInstance();
	if (x > mgm->x) objectDirection = LEFT;
	else if (x < mgm->x) objectDirection = RIGHT;

	if (x == oldRect.x&&y == oldRect.y)
	{
		vx = 0.4*objectDirection;
		vy = 0.7f;
	}
	else
	{
		if (isOnGround)
		{
			vx = 0;
			vy = 0;
		}
	}
	
	setCurAction(PKM_ATTACK);
	if (timeAttack.isReady()&&!timeDefend.isSchedule())
		timeAttack.start((rand()%2+1)*2000+100);
	if (timeAttack.isSchedule())
	{
		setCurAction(PKM_ATTACK);
		
	}
	if (timeDefend.isSchedule())
	{
		setCurAction(PKM_DEFEND);
	}
	timeAttack.isFinish();
	if (timeDefend.isReady() && !timeAttack.isSchedule())
		timeDefend.start();
	timeDefend.isFinish();


	isOnGround = false;
	timeAttack.update();
	timeDefend.update();
	updateFrameAnimation();
	deltaUpdate();
}
void PicketMan::updateFrameAnimation()
{
	timeFrame._tickPerFrame = 200;
	if (sprite == 0)
		return;
	MGMBox::update();
	if (timeFrame.at()) {
		if (curAction==PKM_ATTACK && curFrame == this->sprite->animations[curAction]._framesCount - 1)
			AxeThrowing();
		this->sprite->Update(curAction, curFrame);
	}
	
}
void PicketMan::AxeThrowing()
{
	PKMWeapon *PKMwp = new PKMWeapon();
	PKMwp->objectDirection = this->objectDirection;
	PKMwp->x = this->x;
	PKMwp->y = this->y;

	float d = Megaman::getInstance()->x - this->x;
	PKMwp->vy = 0.7f ;
 	PKMwp->dx = objectDirection*abs(d*PKMwp->ay * 3 / PKMwp->vy);
}
void PicketMan::onLastFrameAnimation(int action)
{
	if (action == PKM_ATTACK)
	{
	
		AxeThrowing();
	}
}
void PicketMan::render()
{
	MGMEnemy::render();
}
void PicketMan::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET) {
		//count++;
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (this->curAction == PKM_ATTACK) {
			count++;
			if (count == 5)
			{
				//mgmbullet->x = this->x;
				//mgmbullet->y = this->y;
				//mgmbullet->setAction(FIRE);
				isKill = true;
				count = 0;
				EffectCreateItem::getInstance()->enemy = this;
				EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
			}
			MGMAudioManager::getInstance()->Play(AUDIO_ENEMY_DAMAGE);
		}
		else{
			MGMAudioManager::getInstance()->Play(AUDIO_DINK);
			/*mgmbullet->setAction(NONE);*/
		}
	}
}

void PicketMan::onCollision(MGMBox * otherObject, int nx, int ny)
{
	if (ny == 1)
	{
		isOnGround = true;
	}
	MGMEnemy::onCollision(otherObject, nx, ny);
}

PicketMan::PicketMan()
{
	vx = 0;
	vy = 0;
	timeDefend.init(1000);
	categoryEnemy = CREP_PICKET_MAN;
	CountAttack = 0;
	isKill = false;
	
}


PicketMan::~PicketMan()
{
}
