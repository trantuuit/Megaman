#pragma once
#include "MGMEnemy.h"
class PicketMan :
	public MGMEnemy
{
public:
	void update();
	void render();

	void onCollision(MGMBox* otherObject, int nx, int ny);
	PicketMan();
	~PicketMan();
};

