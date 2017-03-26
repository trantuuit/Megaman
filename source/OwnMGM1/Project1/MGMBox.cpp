#include "MGMBox.h"
#include<cmath>

MGMBox::MGMBox()
{
	collisionCategory = CC_GROUND;
}

void MGMBox::update()
{
	isChangeDelta = false;
	isCollision = false;
}


void MGMBox::onInterserct(MGMBox * other)
{
}

void MGMBox::onCollision(MGMBox* other, int nx, int ny)
{

}

void MGMBox::updateLocation()
{
	if (isCollision && !isChangeDelta)
	{
		if (abs(dx) > abs(dy))
			dy = 0;
		else
			dx = 0;
	}
	x += dx;
	y += dy;
}

MGMBox::~MGMBox()
{
}
