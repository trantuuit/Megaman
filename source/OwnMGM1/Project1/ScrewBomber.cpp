#include "ScrewBomber.h"
#include"Megaman.h"
#include"EnemyBullet.h"
#include"MGMCamera.h"
#include "MegamanBullet.h"
#include"EffectCreateItem.h"
#include"MGMAudioManager.h"
ScrewBomber::ScrewBomber()
{
	vx = 0;
	vy = 0;
	ay = 0;
	timeAttack.init(1000);
	timeSleep.init(700);
	categoryEnemy = CREP_SCREW_BOMBER;
}


ScrewBomber::~ScrewBomber()
{ 
	
}

void ScrewBomber::update()
{
	if (delayShot.isReady()) delayShot.start(600);
	delayShot.update();

	Megaman*mgm = Megaman::getInstance();
	if (abs(x - mgm->x) <= 85)
	{
		if (timeAttack.isReady() && !timeSleep.isSchedule()) timeAttack.start();

		if (timeSleep.isReady() && !timeAttack.isSchedule()) timeSleep.start();
		if (timeSleep.isSchedule()) setCurAction(SLEEP);
		timeSleep.isFinish();
	}
	else if (!timeAttack.isSchedule()) setCurAction(SLEEP);

	if (timeAttack.isSchedule())
	{
		setCurAction(ATTACK);
		
		
		if (delayShot.isFinish())
		{
			MGMAudioManager::getInstance()->Play(AUDIO_ENEMY_SHOOT);
			CreateBullet();
		}
	}
	timeAttack.isFinish();

	timeAttack.update();
	timeSleep.update();
	updateFrameAnimation();
}
void ScrewBomber::setCurAction(int action)
{
	prvHeight = this->sprite->animations[curAction].frames[curFrame].height;
	if (action == SLEEP)
		this->height = 8;
	else this->height = 16;
	MGMObject::setCurAction(action);
	int CurHeight = this->sprite->animations[curAction].frames[curFrame].height;
	if(id!= 100 + SPR_SCREWBOMBER)
		y = y + CurHeight - prvHeight;
}
void ScrewBomber::render()
{
	float xDraw, yDraw;
	MGMCamera::getInstance()->Transform(x, y, xDraw, yDraw);
	if (id== 100 + SPR_SCREWBOMBER)
	{
		int heightSprite = sprite->animations[curAction].frames[curFrame].height;
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			1, 0, 0, 0,
			0,-1, 0, 0,
			0, 0, 1, 0,
			0, 2 * (yDraw + heightSprite / 2), 0, 1)));
	}

	this->sprite->Render(xDraw, yDraw, curAction, curFrame);

	if (id ==100+SPR_SCREWBOMBER)
	{
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)));
	}
}
void ScrewBomber::CreateBullet()
{
	if (id != 100 + SPR_SCREWBOMBER)
	{
		EnemyBullet *newBullet1 = new EnemyBullet();
		newBullet1->objectDirection = RIGHT;
		newBullet1->categoryBullet = FOR_SCREW_BOMBER;
		newBullet1->dx = 0;
		newBullet1->dy = 3;
		newBullet1->x = this->x + 5;
		newBullet1->y = this->y + 1;

		EnemyBullet *newBullet2 = new EnemyBullet();
		newBullet2->objectDirection = LEFT;
		newBullet2->categoryBullet = FOR_SCREW_BOMBER;
		newBullet2->dx = -3;
		newBullet2->dy = 0;
		newBullet2->x = this->x - 1;
		newBullet2->y = this->y - 1;

		EnemyBullet *newBullet3 = new EnemyBullet();
		newBullet3->objectDirection = RIGHT;
		newBullet3->categoryBullet = FOR_SCREW_BOMBER;
		newBullet3->dx = 3;
		newBullet3->dy = 0;
		newBullet3->x = this->x + 9;
		newBullet3->y = this->y - 1;

		EnemyBullet *newBullet4 = new EnemyBullet();
		newBullet4->objectDirection = LEFT;
		newBullet4->categoryBullet = FOR_SCREW_BOMBER;
		newBullet4->dx = -3;
		newBullet4->dy = 3;
		newBullet4->x = this->x - 1;
		newBullet4->y = this->y + 1;

		EnemyBullet *newBullet5 = new EnemyBullet();
		newBullet5->objectDirection = RIGHT;
		newBullet5->categoryBullet = FOR_SCREW_BOMBER;
		newBullet5->dx = 3;
		newBullet5->dy = 3;
		newBullet5->x = this->x + 9;
		newBullet5->y = this->y + 1;
	}
	else
	{
		EnemyBullet *newBullet1 = new EnemyBullet();
		newBullet1->objectDirection = RIGHT;
		newBullet1->categoryBullet = FOR_SCREW_BOMBER;
		newBullet1->dx = 0;
		newBullet1->dy = -3;
		newBullet1->x = this->x + 5;
		newBullet1->y = this->y - 9;

		EnemyBullet *newBullet2 = new EnemyBullet();
		newBullet2->objectDirection = LEFT;
		newBullet2->categoryBullet = FOR_SCREW_BOMBER;
		newBullet2->dx = -3;
		newBullet2->dy = 0;
		newBullet2->x = this->x + 5;
		newBullet2->y = this->y - 9;

		EnemyBullet *newBullet3 = new EnemyBullet();
		newBullet3->objectDirection = RIGHT;
		newBullet3->categoryBullet = FOR_SCREW_BOMBER;
		newBullet3->dx = 3;
		newBullet3->dy = 0;
		newBullet3->x = this->x + 5;
		newBullet3->y = this->y - 9;

		EnemyBullet *newBullet4 = new EnemyBullet();
		newBullet4->objectDirection = LEFT;
		newBullet4->categoryBullet = FOR_SCREW_BOMBER;
		newBullet4->dx = -3;
		newBullet4->dy = -3;
		newBullet4->x = this->x + 5;
		newBullet4->y = this->y - 9;

		EnemyBullet *newBullet5 = new EnemyBullet();
		newBullet5->objectDirection = RIGHT;
		newBullet5->categoryBullet = FOR_SCREW_BOMBER;
		newBullet5->dx = 3;
		newBullet5->dy = -3;
		newBullet5->x = this->x + 5;
		newBullet5->y = this->y - 9;
	}
}

void  ScrewBomber::onCollision(MGMBox * otherObject, int nx, int ny){
	
}
void ScrewBomber::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		count++;
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (count == 3){

			mgmbullet->x = this->x;
			mgmbullet->y = this->y;
			mgmbullet->setAction(FIRE);
			isKill = true;
			count = 0;
			Megaman::getInstance()->score += 500;
			EffectCreateItem::getInstance()->enemy = this;
			EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
		}
		else{
			MGMAudioManager::getInstance()->Play(AUDIO_DINK);
			mgmbullet->setAction(NONE);
		}
	}
}