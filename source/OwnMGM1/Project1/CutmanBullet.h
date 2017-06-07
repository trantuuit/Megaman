#pragma once
#include "MGMEnemy.h"
#include"MGMSpriteManager.h"
#include "MGMGameTime.h"
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

enum DIRECTION_X
{
	C_LEFT = -1,
	C_RIGHT = 1,
};
enum DIRECTION_Y
{
	C_TOP = 1,
	C_BOTTOM = -1
};
class CutmanBullet :
	public MGMEnemy
{
private:
	fstream fileLog;
	bool isThrow;
	bool isBack;
	DIRECTION_X directionX, backDirectionX;
	DIRECTION_Y directionY, backDirectionY;
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
	void update();
	void render();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void onIntersectRect(MGMBox* otherObject);
	CutmanBullet();
	~CutmanBullet();
};

