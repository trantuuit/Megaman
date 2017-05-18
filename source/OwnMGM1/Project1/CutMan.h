#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"
enum CUTMAN_ACTION{
	CM_STAND,
	CM_JUMP,
	CM_RUN,
	CM_STAND_ATTACK,
	CM_ATTACK
};
class CutMan :
	public MGMEnemy
{
private:
	static CutMan* cutman;
	boolean isOnGround;
	CUTMAN_ACTION action;
	boolean attackBullet;
	MGMDelayTime jumpTime;
	MGMDelayTime standTime;
	MGMDelayTime runTime;
	MGMDelayTime standAttackTime;
	MGMDelayTime attackTime;
public:
	static CutMan* getInstance();
	void update();
	void movingUpdate();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	CutMan();
	~CutMan();
};

