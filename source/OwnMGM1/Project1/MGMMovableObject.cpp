#include "MGMMovableObject.h"



MGMMovableObject::MGMMovableObject()
{
	ax = 0;
	vx = 0.3;
}

void MGMMovableObject::updateMove()
{
	vx = vx + ax*gameTime;
	dx = vx*gameTime;

	vy = vy + ay*gameTime;
	dy = vy*gameTime;
}

void MGMMovableObject::update()
{
	MGMObject::update();
	updateMove();
}

MGMMovableObject::~MGMMovableObject()
{
}
