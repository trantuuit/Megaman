#include "OctopusBattery.h"
#include "Megaman.h"
#include "MegamanBullet.h"
#include"EffectCreateItem.h"
#include"MGMAudioManager.h"
void OctopusBattery::update()
{

	switch (OctActivity)
	{
	case OCTOPUSBATTERY_OPEN:
		//pauseAnimation = true;
		curFrame = 0;
		if (id == 102){
			dy = (int)(vy*GAMETIME);
			return;
		}
		dx = (int)(vx*GAMETIME);
		break;
	case OCTOPUSBATTERY_CLOSE:
		if (delayCloseActivity.isReady()){
			delayCloseActivity.start();
		}
		if (delayCloseActivity.isSchedule()){
			dx = 0;
			dy = 0;
			curFrame = 2;
		}
		if (delayCloseActivity.isFinish())
		{
			//pauseAnimation = false;
			OctActivity = OCTOPUSBATTERY_OPEN;
		}
		delayCloseActivity.update();
		break;
	case OCTOPUSBATTERY_RUN_CLOSE:
		if (delayRunCloseActivity.isReady()){
			delayRunCloseActivity.start();
		}
		if (delayRunCloseActivity.isSchedule()){
			dx = 0;
			dy = 0;
			curFrame = 1;
		}
		if (delayRunCloseActivity.isFinish())
		{
			//pauseAnimation = false;
			OctActivity = OCTOPUSBATTERY_CLOSE;
		}
		delayRunCloseActivity.update();
		break;
	default:
		break;
	}
	isPreventMove = true;
	
}
void OctopusBattery::render(){
	MGMEnemy::render();
}
void OctopusBattery::onCollision(MGMBox * otherObject, int nx, int ny){
	if (otherObject->collisionCategory == CC_GROUND)
	{
		if (nx != 0){
			vx = (abs)(vx)* nx;
			OctActivity = OCTOPUSBATTERY_RUN_CLOSE;
			return;
		}
		if (id == 102){
			if (ny != 0){
				vy = (abs)(vy)*ny;
				OctActivity = OCTOPUSBATTERY_RUN_CLOSE;
				return;
			}
		}
	}
}
void OctopusBattery::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		count++;
		if (count == 5){

			mgmbullet->x = this->x;
			mgmbullet->y = this->y;
			mgmbullet->setAction(FIRE);
			isKill = true;
			count = 0;
			Megaman::getInstance()->score += 300;
			EffectCreateItem::getInstance()->enemy = this;
			EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
		}
		else{
			MGMAudioManager::getInstance()->Play(AUDIO_ENEMY_DAMAGE);
			mgmbullet->setAction(NONE);
		}
	}
}
OctopusBattery::OctopusBattery()
{
	pauseAnimation = false;
	delayRunCloseActivity.init(150);
	delayCloseActivity.init(1300);
	curAction = 0;
	curFrame = 2;
	vx = -0.4f;
	vy = -0.4f;
	ay = 0;
	ax = 0;
	categoryEnemy = CREP_OCTOPUS_BATTERY;
}


OctopusBattery::~OctopusBattery()
{
}
