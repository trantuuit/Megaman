#include "MGMRectangle.h"


MGMRectangle::MGMRectangle()
{
}
MGMRectangle::MGMRectangle(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}
void MGMRectangle::init(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}


RECT MGMRectangle::toRect()
{
	RECT r;
	SetRect(&r, getLeft(), getTop(), getRight(), y+height);
	return r;
}

int MGMRectangle::getLeft()
{
	return x;
}
int MGMRectangle::getTop()
{
	return y;

}
int MGMRectangle::getRight()
{
	return x + width;

}
int MGMRectangle::getBottom()
{
	return y - height;

}
int MGMRectangle::getXCenter()
{
	return x + width / 2;
}
int MGMRectangle::getYCenter()
{
	return y - height / 2;
}
MGMRectangle::~MGMRectangle()
{
}
