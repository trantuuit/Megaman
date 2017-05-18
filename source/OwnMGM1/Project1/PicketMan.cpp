#include "PicketMan.h"
#include"Megaman.h"
#include"Collision.h"


void PicketMan::update()
{
	MGMEnemy::update();
}

void PicketMan::render()
{
	MGMEnemy::render();
}

void PicketMan::onCollision(MGMBox * otherObject, int nx, int ny)
{
	MGMEnemy::onCollision(otherObject, nx, ny);
	if (otherObject->collisionCategory == CC_GROUND)
	{
		if(nx!=0)
			vx = abs(vx)*nx;
	}
	if (otherObject == Megaman::getInstance())
	{
		Collision::preventMove(Megaman::getInstance(), this, nx,ny);
	}
}

PicketMan::PicketMan()
{
	curAction = 1;
	curFrame = 0;
}


PicketMan::~PicketMan()
{
}
