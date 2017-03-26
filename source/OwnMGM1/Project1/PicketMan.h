#pragma once
#include "MGMEnemy.h"
class PicketMan :
	public MGMEnemy
{
public:
	void update();
	void render();

	PicketMan();
	~PicketMan();
};

