#include "CutMan.h"
#include "CutmanBullet.h"
#include "Megaman.h"
#include "Door.h"
CutMan* CutMan::cutman = 0;
CutMan* CutMan::getInstance(){
	if (cutman == 0){
		cutman = new CutMan();
	}
	return cutman;
}
CutMan::CutMan()
{
	curAction = 0;
	curFrame = 0;
	vx = 1;
	vy = -0.9f;
	ay = GRAVITY;
	objectDirection = LEFT;
	isOnGround = false;
	standTime.init(500);
	jumpTime.init(200);
	runTime.init(1000);
	action = CM_STAND;
	attackBullet = false;
}

void CutMan::update(){
	MGMEnemy::updateFrameAnimation();
	movingUpdate();
}
void CutMan::movingUpdate(){
	if (Megaman::getInstance()->getXCenter() < this->getXCenter()){
		objectDirection = LEFT;
	}
	else{
		objectDirection = RIGHT;
	}
	switch (action)
	{
	case CM_STAND:
		curAction = 0;
		if (standTime.isReady()){
			standTime.start();
		}
		if (standTime.isOnTime()){
			
			dx = 0;
		}
		else{
			action = CM_JUMP;
		}
		standTime.update();
		dy = -10;
		break;
	case CM_JUMP:
		curAction = 1;
		if (jumpTime.isReady()&&jumpTime.isTerminated()){
			jumpTime.start();
		}
		if (jumpTime.isOnTime()){
			dy = 5;

		}
		else{
			if (isOnGround){
				dy = -5;
			}
			action = CM_RUN;
		}
		jumpTime.update();
		break;
	case CM_RUN:
		curAction = 2;
		dx = -1;
		if (runTime.isReady()){
			runTime.start();
		}
		if (runTime.isOnTime()){
			dx = -1;
		}
		else{
			action = CM_STAND_ATTACK;
			dx = 0;
		}
		runTime.update();
		dy = -9;
		break;
	case CM_STAND_ATTACK:
		curAction = 3;
		curFrame = 1;
		if (!attackBullet){
			CutmanBullet::getBullet()->x = this->x;
			CutmanBullet::getBullet()->y = this->y;
			//CutmanBullet::getBullet()->dx = -1;
			//CutmanBullet::getBullet()->dy = 0;
			attackBullet = true;
		}
		dy = -9;
		break;
	case CM_ATTACK:
		break;
	default:
		
		break;
	}
}
void CutMan::onCollision(MGMBox* otherObject, int nx, int ny){
	MGMEnemy::onCollision(otherObject, nx, ny);
	if (ny == 1)
	{
		isOnGround = true;
	}
	//if (nx == 1){
	//	action = CM_JUMP;
	//}
	if (otherObject == Megaman::getInstance())
	{
		
		Collision::preventMove(Megaman::getInstance(), this,nx,ny);
	}
	MGMObject* temp = (MGMObject*)otherObject;
	if (temp->collisionCategory==CC_DOOR){
		Collision::preventMove(CutMan::getInstance(), temp, nx, ny);
	}
}
CutMan::~CutMan()
{
}
