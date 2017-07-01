#include "MGMBox.h"
#include<cmath>

MGMBox::MGMBox()
{
	collisionCategory = CC_GROUND;
}

MGMBox::MGMBox(float x, float y, float width, float height)
{
	collisionCategory = CC_GROUND;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

void MGMBox::init(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
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
	if (isCollision && !isPreventMove)
	{
		dy = 0;
	}
	x += dx;
	y += dy;

}

RECT MGMBox::toRect()
{
	RECT r;
	SetRect(&r, getLeft(), getTop(), getRight() + 1, y + height);
	return r;
}

int MGMBox::getLeft()
{
	return x;
}
int MGMBox::getTop()
{
	return y;

}
int MGMBox::getRight()
{
	return x + width - 1;

}
int MGMBox::getBottom()
{
	return y - height + 1;

}
int MGMBox::getXCenter()
{
	return x + width / 2;
}
int MGMBox::getYCenter()
{
	return y - height / 2;
}

MGMBox::~MGMBox()
{
}
