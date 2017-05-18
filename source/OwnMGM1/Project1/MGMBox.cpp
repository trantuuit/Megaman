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


void MGMBox::onInterserct(MGMBox * otherObject)
{
}

void MGMBox::onCollision(MGMBox* otherObject, int nx, int ny)
{

}

void MGMBox::terrainUpdate()
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
