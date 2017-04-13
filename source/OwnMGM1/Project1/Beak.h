#pragma once
#include "MGMEnemy.h"
#include "Megaman.h"
#include"BeakBullet.h"
#include"MGMCamera.h"
#include"MGMDelayTime.h"

enum BEAK_ACTIVITY //Phân loại hoạt động
{
	BEAK_OPEN,
	BEAK_CLOSE
};

enum BEAK_BULLET //Phân loại đạn theo hướng bay
{
	BULLET_1,
	BULLET_2,
	BULLET_3,
	BULLET_4
};


class Beak :
	public MGMEnemy
{
	BEAK_BULLET bulletType;
	BEAK_ACTIVITY beakActivity;
	MGMDelayTime delayActivity;

	MGMDelayTime delayShoot; //Thời gian ngưng giữa 2 viên đạn
	MGMDelayTime timeShoot; // Khoảng thời gian bắn đủ 4 viên đạn
	bool pauseAnimation;
public:
	void update();
	void render();
	void onCollision(MGMBox *other, int nx, int ny);
	void onLastFrameAnimation(int action);
	Beak();
	~Beak();
};

