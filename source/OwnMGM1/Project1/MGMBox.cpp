#include "MGMBox.h"
#include<cmath>

MGMBox::MGMBox()
{
	collisionCategory = CC_GROUND;
}

void MGMBox::update()
{
	isPreventMove = true;
	isCollision = false;
}


void MGMBox::onIntersectRect(MGMBox * otherObject)
{
}

void MGMBox::onCollision(MGMBox* otherObject, int nx, int ny)
{

}

void MGMBox::coordinateUpdate()
{
	if (isCollision && !isPreventMove )
	{
		dy = 0;
	}
	x += dx;
	y += dy;
}

MGMBox::~MGMBox()
{
}
