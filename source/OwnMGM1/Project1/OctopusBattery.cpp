#include "OctopusBattery.h"
#include "Megaman.h"


void OctopusBattery::update()
{
	switch (OctActivity)
	{
	case OCTOPUSBATTERY_OPEN:
		pauseAnimation = false;
		curFrame = 0;
		if ((oldRect.x == 1344 && oldRect.y == 1038) || (oldRect.x == 1376 && oldRect.y == 1102)
			|| (oldRect.x == 1360 && oldRect.y == 1309) || (oldRect.x == 1408 && oldRect.y == 1502)
			|| (oldRect.x == 1473 && oldRect.y == 1886) || (oldRect.x == 1328 && oldRect.y == 1805)){
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
			pauseAnimation = false;
			OctActivity = OCTOPUSBATTERY_OPEN;
		}
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
			pauseAnimation = false;
			OctActivity = OCTOPUSBATTERY_CLOSE;
		}
		break;
	default:
		break;
	}
	delayCloseActivity.update();
	delayRunCloseActivity.update();
	/*MGMEnemy::updateFrameAnimation();*/
	/*MGMEnemy::update();*/
	//if ((oldRect.x == 1344 && oldRect.y == 1040) || (oldRect.x == 1376 && oldRect.y == 1104)
	//	|| (oldRect.x == 1360 && oldRect.y == 1311) || (oldRect.x == 1408 && oldRect.y == 1504)
	//	|| (oldRect.x == 1473 && oldRect.y == 1887) || (oldRect.x == 1328 && oldRect.y==1807)){
	//	dy = (int)(vy*GAMETIME);
	//	/*dy = 0;*/
	//	return;
	//}
	//else{
	//	dx = (int)(vx*GAMETIME);
	//}
	/*dx = (int)(vx*GAMETIME);*/
	//if (!pauseAnimation)
	//	MGMObject::updateFrameAnimation();
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
	//if (other->collisionCategory == CC_MEGAMAN)
	//	Collision::preventMove(other, this);
}
void OctopusBattery::onLastFrameAnimation(int action){
	//if (OctActivity == OCTOPUSBATTERY_CLOSE){
	//	delayActivity.start();
	//	curFrame = 1;
	//}
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
