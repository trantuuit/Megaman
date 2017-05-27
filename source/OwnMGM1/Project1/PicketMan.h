#pragma once
#include "MGMEnemy.h"
#include"MGMDelayTime.h"
enum
{
	PKM_DEFEND,
	PKM_ATTACK
};
class PicketMan :
	public MGMEnemy
{
	int CountAttack;
	MGMDelayTime timeAttack;
	MGMDelayTime timeDefend;
public:
	void update();
	void updateFrameAnimation();
	void AxeThrowing();
	void onLastFrameAnimation(int action);
	void render();

	bool jump;
	void onIntersectRect(MGMBox* otherObject);
	void onCollision(MGMBox* otherObject, int nx, int ny);
	PicketMan();
	~PicketMan();
};

