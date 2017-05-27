#pragma once
#include "MGMEnemy.h"
#include"MGMDelayTime.h"
enum
{
	MET_SLEEP,
	MET_ATTACK
};
class Met :
	public MGMEnemy
{
	MGMDelayTime timeAttack;
	MGMDelayTime timeSleep;
	int CountShot;
public:
	Met();
	~Met();
	void update();
	void CreateBullet();
	void onIntersectRect(MGMBox* otherObject);
	void onCollision(MGMBox * otherObject, int nx, int ny);
};

