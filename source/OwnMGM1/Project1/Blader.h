#pragma once
#include "MGMEnemy.h"
class Blader :
	public MGMEnemy
{
public:
	void update();
	void render();
	void updateMove();
	void onCollision(MGMBox* other, int nx, int ny);
	Blader();
	~Blader();
};

