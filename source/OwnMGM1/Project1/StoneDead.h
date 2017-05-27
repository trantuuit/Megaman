#pragma once
#include "MGMEnemy.h"
class StoneDead :
	public MGMEnemy
{
public:
	StoneDead();
	void onIntersectRect(MGMBox* otherObject);
	~StoneDead();
};

