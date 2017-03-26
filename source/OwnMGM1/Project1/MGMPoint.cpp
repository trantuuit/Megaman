#include "MGMPoint.h"

MGMPoint::MGMPoint(int x, int y)
{
	set(x, y);
}

void MGMPoint::set(int x, int y)
{
	X = x;
	Y = y;
}


MGMPoint::~MGMPoint()
{
}
