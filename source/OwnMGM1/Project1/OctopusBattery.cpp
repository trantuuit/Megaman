#include "OctopusBattery.h"
#include "Megaman.h"
#include "MegamanBullet.h"

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
		if (delayCloseActivity.isOnTime()){
			dx = 0;
			dy = 0;
			curFrame = 2;
		}
		if (delayCloseActivity.isTerminated())
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
		if (delayRunCloseActivity.isOnTime()){
			dx = 0;
			dy = 0;
			curFrame = 1;
		}
		if (delayRunCloseActivity.isTerminated())
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
			/*this->curFrame = 2;*/
			vx = (abs)(vx)* nx;
			OctActivity = OCTOPUSBATTERY_RUN_CLOSE;
			return;
		}
		if (id == 102){
			if (ny != 0){
				vy = (abs)(vy)*ny;
				OctActivity = OCTOPUSBATTERY_RUN_CLOSE;
				/*this->curFrame = 2;*/
				return;
			}
		}

		//if (ny == 1){
		//	dy = 1;
		//}
		//if (ny == -1){
		//	vy = abs(vy)*ny;
		//}

	}
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		count++;
		if (count == 5){

			mgmbullet->x = this->x;
			mgmbullet->y = this->y;
			mgmbullet->setAction(FIRE);
			isKill = true;
			count = 0;
		}
		else{
			mgmbullet->setAction(NONE);
		}
	}
}

OctopusBattery::OctopusBattery()
{
	pauseAnimation = false;
	this->width = this->height = 16;
	delayRunCloseActivity.init(150);
	delayCloseActivity.init(1300);
	curAction = 0;
	curFrame = 2;
	vx = -0.4f;
	vy = -0.4f;
	ay = 0;
	ax = 0;
}


OctopusBattery::~OctopusBattery()
{
}
