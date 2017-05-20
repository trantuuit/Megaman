#pragma once
#include "MGMMovableObject.h"
#include"List.h"
#include "MGMDelayTime.h"
enum CATEGORY_ITEM{
	CI_BONUS_BALL,
	CI_LIFE_ENERGY_BIG,
	CI_LIFE_ENERGY_SMALL,
	CI_UP,
	CI_WEAPON_ENERGY_BIG,
	CI_WEAPON_ENERGY_SMALL,
	CI_YASHICHI,
};
class MGMItem :
	public MGMMovableObject
{
private:
	static List<MGMItem*>* listItem;
	MGMDelayTime timeDie;
public:
	CATEGORY_ITEM categoryItem;
	static List<MGMItem*>* getListItem();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void CountDownDie();
	void update();
	void onIntersectRect(MGMBox* otherObject);
	MGMItem();
	~MGMItem();
};

