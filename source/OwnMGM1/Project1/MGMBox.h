#pragma once
#include"MGMRectangle.h"

enum COLLISION_CATEGORY
{
	CC_ENEMY,
	CC_GROUND,
	CC_ITEM,
	CC_STAIRS,
	CC_ENEMY_BULLET,
	CC_MGM_BULLET,
	CC_MEGAMAN,
	CC_DOOR
};

class MGMBox : public MGMRectangle
{
public:
	int dx, dy;
	float vx, ax, vy, ay;
	MGMBox();
	~MGMBox();

	COLLISION_CATEGORY collisionCategory;

	bool isCollision;
	bool isChangeDelta;

	virtual void update();

	virtual void onInterserct(MGMBox* other);
	virtual void onCollision(MGMBox* other, int nx, int ny);
	virtual void updateLocation();

};