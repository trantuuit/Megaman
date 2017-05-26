#include "Flea.h"
#include"Megaman.h"
#include<ctime>
#include "MegamanBullet.h"
#include"EffectCreateItem.h"

Flea::Flea()
{
	vx = 0;
	vy = 0;
	ax = 0;
	timeSit.init(800);
	categoryEnemy = CREP_FLEA;
}

void Flea::update()
{
	if (this->x < Megaman::getInstance()->x)
		objectDirection = RIGHT;
	else objectDirection = LEFT;

	if (isOnGround)
	{
		vx = 0;
		setCurAction(FLEA_SIT);
		if (timeSit.isReady())
			timeSit.start();
		if (timeSit.isFinish())
		{
			this->SetVy();
		}
	}
	else setCurAction(FLEA_JUMP);


	isOnGround = false;
	this->deltaUpdate();
	timeSit.update();
}
void Flea::restoreObject()
{
	x = oldRect.x;
	y = oldRect.y;
	vy = 0;
}
void Flea::SetVy()
{
	srand(time(0));
	int a = rand() % 2;
	if (a == 0)
	{
		vx = objectDirection*0.3f;
		vy = 0.9f;
	}
	else
	{
		vx = objectDirection*0.5f;
		vy = 0.8f;
	}

}
void Flea::deltaUpdate()
{
	vx = vx + ax*GAMETIME;
	dx = (int)(vx*GAMETIME);

	vy = vy + ay*GAMETIME;
	dy = (vy*GAMETIME);
}

void Flea::onCollision(MGMBox * otherObject, int nx, int ny)
{
	if (ny == 1)
	{
		isOnGround = true;
	}
	MGMMovableObject::onCollision(otherObject, nx, ny);
}
void Flea::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		mgmbullet->x = this->x;
		mgmbullet->y = this->y;
		mgmbullet->setAction(FIRE);
		isKill = true;
		Megaman::getInstance()->score += 300;
		EffectCreateItem::getInstance()->enemy = this;
		EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;
	}
}
void Flea::setCurAction(int action)
{
	prvHeight = this->sprite->animations[curAction].frames[curFrame].height;
	if (action == FLEA_SIT) 
		this->height = 10;
	else this->height = 19;
	MGMMovableObject::setCurAction(action);
	int CurHeight= this->sprite->animations[curAction].frames[curFrame].height;
	y = y+ CurHeight -prvHeight;
	
}
void Flea::render()
{
	MGMEnemy::render();
}

Flea::~Flea()
{
}
