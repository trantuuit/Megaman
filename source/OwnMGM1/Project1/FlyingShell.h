#pragma once
#include "MGMEnemy.h"
#include"MGMDelayTime.h"
#include"BeakBullet.h"
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
	void onCollision(MGMBox *other, int nx, int ny);
	FlyingShell();
	~FlyingShell();
};

