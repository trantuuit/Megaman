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
	MGMObject::update();
	updateMove();
}

MGMMovableObject::~MGMMovableObject()
{
}
