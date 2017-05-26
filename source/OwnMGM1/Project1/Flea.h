#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"
enum FLEA_ACTION
{
	FLEA_SIT,
	FLEA_JUMP
};
class Flea :
	public MGMEnemy
{
public:
	Flea();
	int prvHeight;
	void onCollision(MGMBox * otherObject, int nx, int ny);
	void onIntersectRect(MGMBox* otherObject);
	void setCurAction(int action);
	void update();
	void restoreObject();
	void SetVy();
	void deltaUpdate();
	void render();
	MGMDelayTime timeSit;
	~Flea();
};

