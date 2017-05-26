#pragma once
#include "MGMEnemy.h"
#include"MGMDelayTime.h"
#include"EnemyBullet.h"
enum FLYINGSHELL_ACTIVITY //Phân loại hoạt động
{
	FLYINGSHELL_OPEN,
	FLYINGSHELL_CLOSE,

};
class FlyingShell :
	public MGMEnemy
{
private:
	FLYINGSHELL_ACTIVITY flyingShellActivity;
	MGMDelayTime move;
	MGMDelayTime stop;
	MGMDelayTime delayShoot;
public:
	void update();
	void render();
	void onCollision(MGMBox *otherObject, int nx, int ny);
	void onIntersectRect(MGMBox* otherObject);
	FlyingShell();
	~FlyingShell();
};

