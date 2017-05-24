#pragma once
#include "MGMEnemy.h"
class GreenBar :
	public MGMEnemy
{
	const int greenBarDx = 1;
public:
	bool pauseAnimation;
	GreenBar();
	void update();
	void render();
	~GreenBar();
};

