#include "MGMMovableObject.h"



MGMMovableObject::MGMMovableObject()
{
	ax = 0;
	vx = 0.3;
}

void MGMMovableObject::updateMove()
{
	vx = vx + ax*GAMETIME;
	dx = (int)(vx*GAMETIME);

	vy = vy + ay*GAMETIME;
	dy = (vy*GAMETIME);
}



void MGMMovableObject::update()
{
	MGMObject::updateFrameAnimation();
	updateMove();
}

void MGMMovableObject::onCollision(MGMBox * other, int nx, int ny)
{
	if (ny != 0 && other->collisionCategory == CC_GROUND)
	{
		vy = -0.25;
	}
	if (other->collisionCategory == CC_GROUND)
	{
		Collision::preventMove(this, other,nx,ny);
		//if (ny == 1) isOnGround = true;
	}
}

MGMMovableObject::~MGMMovableObject()
{
}
