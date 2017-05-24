#include "MGMMovableObject.h"



MGMMovableObject::MGMMovableObject()
{
	ax = 0;
	vx = 0.3;
}

void MGMMovableObject::deltaUpdate()
{
	vx = vx + ax*GAMETIME;
	dx = (float)(vx*GAMETIME);

	vy = vy + ay*GAMETIME;
	dy = (vy*GAMETIME);
}



void MGMMovableObject::update()
{
	MGMObject::updateFrameAnimation();
	deltaUpdate();
}

void MGMMovableObject::onCollision(MGMBox * otherObject, int nx, int ny)
{
	if (ny != 0 && (otherObject->collisionCategory == CC_GROUND || otherObject->collisionCategory == CC_BIGROCK))
	{
		vy = -0.25;
	}
	if (otherObject->collisionCategory == CC_GROUND || otherObject->collisionCategory == CC_BIGROCK)
	{
		Collision::preventMove(this, otherObject,nx,ny);
	}
}

MGMMovableObject::~MGMMovableObject()
{
}
