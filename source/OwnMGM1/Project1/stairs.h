#pragma once
#include "MGMObject.h"
#include "Megaman.h"
class stairs : public MGMObject
{
public:
	bool isHaveMGM;
	stairs();
	~stairs();
	void onCollision(MGMBox* other, int nx, int ny);
	void climbStairs();
};

