#pragma once
#include "MGMObject.h"
#include "Megaman.h"
#include"MGMDelayTime.h"
class stairs : public MGMObject
{
public:
	MGMDelayTime delay;
	bool isHaveMGM;
	stairs();
	~stairs();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void climbStairs();
};

