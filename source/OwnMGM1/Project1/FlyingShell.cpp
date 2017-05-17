#include "FlyingShell.h"


FlyingShell::FlyingShell()
{
	curAction = 0;
	curFrame = 0;
	vx = -0.2f;
	vy = 0;
	ay = 0;
	objectDirection = LEFT;
	flyingShellActivity = FLYINGSHELL_CLOSE;
}

void FlyingShell::update(){
	switch (flyingShellActivity)
	{
	case FLYINGSHELL_OPEN:
		if (stop.isReady()){
			stop.start(500);
		}
		if (stop.isOnTime()){
			vx = 0;
			curFrame = 1;
			if (!delayShoot.isOnTime()){
				delayShoot.start(500);
				//Ban 8 vien cung 1 luc
				BeakBullet *newBullet1 = new BeakBullet();
				newBullet1->dx = 0;
				newBullet1->dy = 3;
				newBullet1->x = this->x + 8;
				newBullet1->y = this->y+1;

				BeakBullet *newBullet2 = new BeakBullet();
				newBullet2->dy = 3;
				newBullet2->dx = 3;
				newBullet2->x = this->x + 12;
				newBullet2->y = this->y-1;

				BeakBullet *newBullet3 = new BeakBullet();
				newBullet3->dy = 0;
				newBullet3->dx = 3;
				newBullet3->x = this->x + 16;
				newBullet3->y = this->y - 11;

				BeakBullet *newBullet4 = new BeakBullet();
				newBullet4->dy = -3;
				newBullet4->dx = 3;
				newBullet4->x = this->x + 12;
				newBullet4->y = this->y - 11;

				BeakBullet *newBullet5 = new BeakBullet();
				newBullet5->dy = -3;
				newBullet5->dx = 0;
				newBullet5->x = this->x + 8;
				newBullet5->y = this->y - 21;

				BeakBullet *newBullet6 = new BeakBullet();
				newBullet6->dy = -3;
				newBullet6->dx = -3;
				newBullet6->x = this->x;
				newBullet6->y = this->y - 18;

				BeakBullet *newBullet7 = new BeakBullet();
				newBullet7->dy = 0;
				newBullet7->dx = -3;
				newBullet7->x = this->x;
				newBullet7->y = this->y - 11;

				BeakBullet *newBullet8 = new BeakBullet();
				newBullet8->dy = 3;
				newBullet8->dx = -3;
				newBullet8->x = this->x+4;
				newBullet8->y = this->y - 1;
			}
			delayShoot.update();
		}
		if (stop.isTerminated()){
			flyingShellActivity = FLYINGSHELL_CLOSE;
			vx = -0.2f;
		}
		break;
	case FLYINGSHELL_CLOSE:
		if (move.isReady()){
			move.start(1500);
		}
		if (move.isOnTime()){
			curFrame = 0;
		}
		if (move.isTerminated()){
			flyingShellActivity = FLYINGSHELL_OPEN;
		}
		break;
	default:
		break;
	}
	move.update();
	stop.update();
	MGMEnemy::updateMove();
}

void FlyingShell::render(){
	MGMEnemy::render();
}
void FlyingShell::onCollision(MGMBox *other, int nx, int ny){
	if (other->collisionCategory == CC_MEGAMAN_BULLET){
		isKill = true;
	}
}
FlyingShell::~FlyingShell()
{
}
