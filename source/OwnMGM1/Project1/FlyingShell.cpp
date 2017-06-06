#include "FlyingShell.h"
#include "MegamanBullet.h"
#include"Megaman.h"
#include"MGMAudioManager.h"
#include"EffectCreateItem.h"
FlyingShell::FlyingShell()
{
	curAction = 0;
	curFrame = 0;
	vx = -0.2f;
	vy = 0;
	ay = 0;
	objectDirection = LEFT;
	flyingShellActivity = FLYINGSHELL_CLOSE;
	categoryEnemy = CREP_FLYING_SHELL;
}

void FlyingShell::update(){
	switch (flyingShellActivity)
	{
	case FLYINGSHELL_OPEN:
		if (stop.isReady()){
			stop.start(500);
		}
		if (stop.isSchedule()){
			vx = 0;
			curFrame = 1;
			if (!delayShoot.isSchedule()){
				delayShoot.start(500);
				//Ban 8 vien cung 1 luc
				EnemyBullet *newBullet1 = new EnemyBullet();
				
				newBullet1->categoryBullet = FOR_FLYING_SHELL;
				newBullet1->dx = 0;
				newBullet1->dy = 3;
				newBullet1->x = this->x + 8;
				newBullet1->y = this->y + 1;

				EnemyBullet *newBullet2 = new EnemyBullet();
				newBullet2->objectDirection = LEFT;	
				newBullet2->categoryBullet = FOR_FLYING_SHELL;
				newBullet2->dy = 3;
				newBullet2->dx = 3;
				newBullet2->x = this->x + 12;
				newBullet2->y = this->y - 1;

				EnemyBullet *newBullet3 = new EnemyBullet();
				newBullet3->objectDirection = LEFT;
				newBullet3->categoryBullet = FOR_FLYING_SHELL;
				newBullet3->dy = 0;
				newBullet3->dx = 3;
				newBullet3->x = this->x + 16;
				newBullet3->y = this->y - 11;

				EnemyBullet *newBullet4 = new EnemyBullet();
				newBullet4->objectDirection = LEFT;
				newBullet4->categoryBullet = FOR_FLYING_SHELL;
				newBullet4->dy = -3;
				newBullet4->dx = 3;
				newBullet4->x = this->x + 12;
				newBullet4->y = this->y - 11;

				EnemyBullet *newBullet5 = new EnemyBullet();
				newBullet5->categoryBullet = FOR_FLYING_SHELL;
				newBullet5->dy = -3;
				newBullet5->dx = 0;
				newBullet5->x = this->x + 8;
				newBullet5->y = this->y - 21;

				EnemyBullet *newBullet6 = new EnemyBullet();
				newBullet6->objectDirection = RIGHT;
				newBullet6->categoryBullet = FOR_FLYING_SHELL;
				newBullet6->dy = -3;
				newBullet6->dx = -3;
				newBullet6->x = this->x;
				newBullet6->y = this->y - 18;

				EnemyBullet *newBullet7 = new EnemyBullet();
				newBullet7->objectDirection = RIGHT;
				newBullet7->categoryBullet = FOR_FLYING_SHELL;
				newBullet7->dy = 0;
				newBullet7->dx = -3;
				newBullet7->x = this->x;
				newBullet7->y = this->y - 11;

				EnemyBullet *newBullet8 = new EnemyBullet();
				newBullet8->objectDirection = RIGHT;
				newBullet8->categoryBullet = FOR_FLYING_SHELL;
				newBullet8->dy = 3;
				newBullet8->dx = -3;
				newBullet8->x = this->x + 4;
				newBullet8->y = this->y - 1;
				MGMAudioManager::getInstance()->Play(AUDIO_ENEMY_SHOOT);
			}
			delayShoot.update();
		}
		if (stop.isFinish()){
			flyingShellActivity = FLYINGSHELL_CLOSE;
			vx = -0.2f;
		}
		break;
	case FLYINGSHELL_CLOSE:
		if (move.isReady()){
			move.start(1500);
		}
		if (move.isSchedule()){
			curFrame = 0;
		}
		if (move.isFinish()){
			flyingShellActivity = FLYINGSHELL_OPEN;
		}
		break;
	default:
		break;
	}
	move.update();
	stop.update();
	MGMEnemy::deltaUpdate();
}

void FlyingShell::render(){
	MGMEnemy::render();
}
void FlyingShell::onCollision(MGMBox *otherObject, int nx, int ny){
	
}
void FlyingShell::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (flyingShellActivity == FLYINGSHELL_OPEN){
			mgmbullet->x = this->x;
			mgmbullet->y = this->y;
			mgmbullet->setAction(FIRE);
			isKill = true;
			Megaman::getInstance()->score += 800;
			EffectCreateItem::getInstance()->enemy = this;
			EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
		}
		else{
			MGMAudioManager::getInstance()->Play(AUDIO_DINK);
			mgmbullet->setAction(NONE);
		}
	}
}
FlyingShell::~FlyingShell()
{
}
