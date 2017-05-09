#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"

enum BigEye_Activity
{
	BIGEYE_STAND,
	BIGEYE_JUMP
};
class BigEye :
	public MGMEnemy
{
	MGMDelayTime delayBeforeJump;
	BigEye_Activity activity;
public:
	BigEye();
	void onCollision(MGMBox *other, int nx, int ny);
	void update();
	void render();
	int ramdomVy();
	~BigEye();
};

