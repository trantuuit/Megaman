#include "ScrewBomber.h"
#include"Megaman.h"
#include"BeakBullet.h"
#include"MGMCamera.h"
#include "MegamanBullet.h"
ScrewBomber::ScrewBomber()
{
	vx = 0;
	vy = 0;
	ay = 0;
	timeAttack.init(1000);
	timeSleep.init(700);
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
		if (timeAttack.isReady() && !timeSleep.isOnTime()) timeAttack.start();

		if (timeSleep.isReady() && !timeAttack.isOnTime()) timeSleep.start();
		if (timeSleep.isOnTime()) setCurAction(SLEEP);
		timeSleep.isTerminated();
	}
	else if (!timeAttack.isOnTime()) setCurAction(SLEEP);

	if (timeAttack.isOnTime())
	{
		setCurAction(ATTACK);
		
		
		if (delayShot.isTerminated())
		{
			CreateBullet();
		}
	}
	timeAttack.isTerminated();

	
	
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
		BeakBullet *newBullet1 = new BeakBullet();
		newBullet1->dx = 0;
		newBullet1->dy = 3;
		newBullet1->x = this->x + 5;
		newBullet1->y = this->y + 1;

		BeakBullet *newBullet2 = new BeakBullet();
		newBullet2->dx = -3;
		newBullet2->dy = 0;
		newBullet2->x = this->x - 1;
		newBullet2->y = this->y - 1;

		BeakBullet *newBullet3 = new BeakBullet();
		newBullet3->dx = 3;
		newBullet3->dy = 0;
		newBullet3->x = this->x + 9;
		newBullet3->y = this->y - 1;

		BeakBullet *newBullet4 = new BeakBullet();
		newBullet4->dx = -3;
		newBullet4->dy = 3;
		newBullet4->x = this->x - 1;
		newBullet4->y = this->y + 1;

		BeakBullet *newBullet5 = new BeakBullet();
		newBullet5->dx = 3;
		newBullet5->dy = 3;
		newBullet5->x = this->x + 9;
		newBullet5->y = this->y + 1;
	}
	else
	{
		BeakBullet *newBullet1 = new BeakBullet();
		newBullet1->dx = 0;
		newBullet1->dy = -3;
		newBullet1->x = this->x + 5;
		newBullet1->y = this->y - 9;

		BeakBullet *newBullet2 = new BeakBullet();
		newBullet2->dx = -3;
		newBullet2->dy = 0;
		newBullet2->x = this->x + 5;
		newBullet2->y = this->y - 9;

		BeakBullet *newBullet3 = new BeakBullet();
		newBullet3->dx = 3;
		newBullet3->dy = 0;
		newBullet3->x = this->x + 5;
		newBullet3->y = this->y - 9;

		BeakBullet *newBullet4 = new BeakBullet();
		newBullet4->dx = -3;
		newBullet4->dy = -3;
		newBullet4->x = this->x + 5;
		newBullet4->y = this->y - 9;

		BeakBullet *newBullet5 = new BeakBullet();
		newBullet5->dx = 3;
		newBullet5->dy = -3;
		newBullet5->x = this->x + 5;
		newBullet5->y = this->y - 9;
	}
}

void  ScrewBomber::onCollision(MGMBox * other, int nx, int ny){
	if (other->collisionCategory == CC_MEGAMAN_BULLET){
		count++;
		MegamanBullet* mgmbullet = (MegamanBullet*)other;
		if (count == 3){

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