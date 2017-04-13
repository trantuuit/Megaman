#pragma once
#include "MGMEnemy.h"
class Flea :
	public MGMEnemy
{
public:
	Flea();
	void update();
	void render();
	~Flea();
};

