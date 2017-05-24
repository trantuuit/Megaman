#include "CutmanBullet.h"
#include "CutMan.h"
#include "Megaman.h"
CutmanBullet* CutmanBullet::bullet = 0;
CutmanBullet* CutmanBullet::getBullet(){
	if (bullet == 0){
		bullet = new CutmanBullet();
	}
	return bullet;
}
CutmanBullet::CutmanBullet()
{
	dx = 0;
	dy = 0;
	action = PRE_ATTACK;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_CUTMANBULLET];
	updateTarget.tickPerFrame = 1000;
	isUpdateTarget = true;
}

void CutmanBullet::deltaUpdate(){
	if (isUpdateTarget){
		xMegeman = Megaman::getInstance()->x;
		yMegeman = Megaman::getInstance()->y;
		xCutman = CutMan::getInstance()->x;
		yCutman = CutMan::getInstance()->y;
		m = (xMegeman - xCutman) / (yMegeman - yCutman);
		isUpdateTarget = false;
	}
	switch (action){
	case PRE_ATTACK:
		if (Megaman::getInstance()->x < this->x){
			objectDirection = LEFT;
		}
		else{
			objectDirection = RIGHT;
		}
		/*m = (3120 - 3204) / (1303 - 1280);*/
		dy = 4 / sqrt(m*m);

		dx = dy * -1;
		//dy = -1 * (y - yTarget) / (x-xTarget );
		//dx = 1 * (x - xTarget) / (y - yTarget);
		//if (this->x < 3088){
		//	dx = 1;
		//	dy = 0;
		//}
		//if (this->y >= 1432){
		//	dx = 1;
		//	dy = -dy;
		//}
		break;
		//case ATTACK:

		//	if (this->x <= 3088){
		//		dx = -dx;
		//		//dy = -dy;
		//	}
		//	dx = 0;
		//	action = PRE_BACK;
		//	break;
	case PRE_BACK:
		if (CutMan::getInstance()->x < this->x){
			objectDirection = LEFT;
		}
		else{
			objectDirection = RIGHT;
		}

		break;
	case BACK:
		if (direction == CUTMANBULLET_RIGHT){
			dx = 1;
			dy = -1;
		}
		if (direction == CUTMANBULLET_LEFT){
			dx = -1;
			dy = 1;
		}
		if (direction == CUTMANBULLET_UP){
			dx = 1;
			dy = 1;
		}
		if (direction == CUTMANBULLET_DOWN){
			dx = -1;
			dy = -1;
		}
		break;
	default:
		break;
	}
}
void CutmanBullet::onCollision(MGMBox* otherObject, int nx, int ny){
	MGMEnemy::onCollision(otherObject, nx, ny);
	if (nx != 0){
		if (nx == 1){
			direction = CUTMANBULLET_RIGHT;
		}
		if (nx == -1){
			direction = CUTMANBULLET_LEFT;
		}

		action = BACK;
	}
	if (ny != 0){
		if (ny == 1){
			direction = CUTMANBULLET_UP;
		}
		if (ny == -1){
			direction = CUTMANBULLET_DOWN;
		}
		action = BACK;
	}
	if (otherObject == CutMan::getInstance()){
		Collision::preventMove(this, CutMan::getInstance(), nx, ny);
	}
}
CutmanBullet::~CutmanBullet()
{
}
