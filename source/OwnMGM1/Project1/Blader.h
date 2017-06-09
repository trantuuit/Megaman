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
	float t;
	float x0mg, y0mg, xenemy, yenemy, x2, y2,x3,y3;
	boolean isCheck;
	boolean isLeft;
	boolean isRight;
	void update();
	void render();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void onIntersectRect(MGMBox* otherObject);
	Blader();
	~Blader();
};

