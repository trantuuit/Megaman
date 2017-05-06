#include "Flea.h"
#include"Megaman.h"
#include<ctime>


Flea::Flea()
{
	vx = 0;
	vy = 0;
	ax = 0;
	timeSit.init(800);
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
		if (timeSit.isTerminated())
		{
			this->SetVy();
		}
	}
	else setCurAction(FLEA_JUMP);


	isOnGround = false;
	this->updateMove();
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
void Flea::updateMove()
{
	vx = vx + ax*GAMETIME;
	dx = (int)(vx*GAMETIME);

	vy = vy + ay*GAMETIME;
	dy = (vy*GAMETIME);
}

void Flea::onCollision(MGMBox * other, int nx, int ny)
{

	if (ny == 1)
	{
		isOnGround = true;
	}
	MGMMovableObject::onCollision(other, nx, ny);
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
