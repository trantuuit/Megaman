#pragma once
#include "MGMEnemy.h"
#include"MGMSpriteManager.h"
#include "MGMGameTime.h"
enum CUTMANBULLET_DIRECTION{
	CUTMANBULLET_LEFT,
	CUTMANBULLET_RIGHT,
	CUTMANBULLET_UP,
	CUTMANBULLET_DOWN,
};
enum CUTMANBULLET_ACTION{
	PRE_ATTACK,
	PRE_BACK,
	//ATTACK,
	BACK
};
class CutmanBullet :
	public MGMEnemy
{
private:
	CUTMANBULLET_ACTION action;
	CUTMANBULLET_DIRECTION direction;
	int xMegeman;
	int yMegeman;
	int xCutman;
	int yCutman;
	float m;
	boolean isUpdateTarget;
	MGMGameTime updateTarget;
public:
	static CutmanBullet * bullet;
	static CutmanBullet* getBullet();
	void deltaUpdate();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	CutmanBullet();
	~CutmanBullet();
};

