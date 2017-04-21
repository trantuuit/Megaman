#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"
enum BLADER_ACTIVITY //Phân loại hoạt động
{
	BLADER_STEP1,
	BLADER_STEP2
};
class Blader :
	public MGMEnemy
{
private:
	int xTarget, yTarget;
	MGMDelayTime attack;
	MGMGameTime updateTarget;
	BLADER_ACTIVITY bladerActivity;
public:
	bool detectMegaman;
	void update();
	void render();
	void updateMove();
	void onCollision(MGMBox* other, int nx, int ny);
	boolean checkNearMegaman();
	void attackMegaman();
	void stopAttack();
	Blader();
	~Blader();
};

