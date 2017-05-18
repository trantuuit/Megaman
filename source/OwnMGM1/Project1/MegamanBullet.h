#pragma once
#include"List.h"
#include "MGMMovableObject.h"
#include"MGMDelayTime.h"
enum MEGAMANBULLET_ACTION{
	FIRE,
	NORMAL,
	NONE
};
class MegamanBullet :
	public MGMMovableObject
{
private:
	MEGAMANBULLET_ACTION action;
	MGMDelayTime timedelay;
	static List<MegamanBullet*>* bullets;
public:
	boolean isKill;
	static List<MegamanBullet*>* getBullets();
	MegamanBullet();
	void update();
	void setAction(MEGAMANBULLET_ACTION);
	void onCollision(MGMBox* otherObject, int nx, int ny);
	~MegamanBullet();
};

