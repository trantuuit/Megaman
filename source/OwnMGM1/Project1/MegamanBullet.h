#pragma once
#include"List.h"
#include "MGMMovableObject.h"
#include"MGMDelayTime.h"
#include"CutmanBullet.h"
enum MEGAMANBULLET_ACTION{
	FIRE,
	NORMAL,
	NONE,
	IS_THROW,
	IS_BACK,
};
enum CATEGORY_BULLET_FOR_MEGAMAN{
	OF_MEGAMAN,
	OF_CUTMAN,
};
class MegamanBullet :
	public MGMMovableObject
{
private:

	MEGAMANBULLET_ACTION action;
	MGMDelayTime timedelay;
	static List<MegamanBullet*>* bullets;
public:
	float t;
	float x0, y0, x1, y1, x2, y2, x3, y3, x4, y4;
	CATEGORY_BULLET_FOR_MEGAMAN category_bullet;
	boolean isKill;
	boolean isThrow;
	boolean isThrowLeft, isThrowRight;
	static List<MegamanBullet*>* getListBullet();
	MegamanBullet();
	MegamanBullet(CATEGORY_BULLET_FOR_MEGAMAN);
	void update();
	//void setAction(MEGAMANBULLET_ACTION);
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void onIntersectRect(MGMBox* otherObject);
	~MegamanBullet();
};

