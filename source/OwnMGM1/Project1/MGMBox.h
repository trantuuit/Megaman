#pragma once
#include<Windows.h>

enum COLLISION_CATEGORY
{
	CC_ENEMY,
	CC_GROUND,
	CC_ITEM,
	CC_STAIRS,
	CC_ENEMY_BULLET,
	CC_MEGAMAN_BULLET,
	CC_MEGAMAN,
	CC_DOOR,
	CC_BIGROCK,
	CC_PKM_WEAPON,
	CC_NONE_CATEGORY
};

class MGMBox
{
public:
	float x, y;
	int width, height;
	//
	float dx, dy;
	float vx, ax, vy, ay;
	MGMBox();
	MGMBox(float x, float y, float width, float height);
	virtual void init(float x, float y, float width, float height);
	~MGMBox();

	COLLISION_CATEGORY collisionCategory;

	bool isCollision;
	bool isPreventMove;

	virtual void update();

	virtual void onIntersectRect(MGMBox* otherObject);
	virtual void onCollision(MGMBox* otherObject, int nx, int ny);
	virtual void coordinateUpdate();
	//
	RECT toRect();

	int getLeft();
	int getTop();
	int getRight();
	int getBottom();

	int getXCenter();
	int getYCenter();

};