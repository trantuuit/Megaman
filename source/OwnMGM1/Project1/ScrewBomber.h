#pragma once
#include "MGMEnemy.h"
#include"MGMDelayTime.h"
enum
{
	SLEEP,
	ATTACK
};
class ScrewBomber :
	public MGMEnemy
{
	MGMDelayTime timeAttack;
	MGMDelayTime timeSleep;
	MGMDelayTime delayShot;
	int prvHeight;
public:
	
	ScrewBomber();
	~ScrewBomber();
	void update();
	void setCurAction(int action);
	void render();
	void CreateBullet();
	void onCollision(MGMBox * otherObject, int nx, int ny);
};

