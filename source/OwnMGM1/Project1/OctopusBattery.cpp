#include "OctopusBattery.h"
#include "Megaman.h"


void OctopusBattery::update()
{
	switch (OctActivity)
	{
	case OCTOPUSBATTERY_OPEN:
		//pauseAnimation = true;
		curFrame = 0;
		if (id==102){
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


}
void OctopusBattery::render(){
	MGMEnemy::render();
}
void OctopusBattery::onCollision(MGMBox * other, int nx, int ny){
	if (other->collisionCategory == CC_GROUND)
	{
		if (nx != 0){
			/*this->curFrame = 2;*/
			vx = (abs)(vx)* nx;
			OctActivity = OCTOPUSBATTERY_RUN_CLOSE;
			return;
		}
			
		if (ny != 0){
			vy = (abs)(vy)*ny;
			OctActivity = OCTOPUSBATTERY_RUN_CLOSE;
			/*this->curFrame = 2;*/
			return;
		}
		
	}
	if (other->collisionCategory == CC_MEGAMAN_BULLET){
		isKill = true;
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
	ax = 0;
}


OctopusBattery::~OctopusBattery()
{
}
