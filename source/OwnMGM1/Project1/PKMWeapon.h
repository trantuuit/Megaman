#pragma once
#include"MGMEnemy.h"
#include"List.h"
#include"EnemyBullet.h"
class PKMWeapon: public MGMEnemy
{
private:
	CATEGORY_BULLET categoryBullet;
public:
	static List<PKMWeapon*>* hammer;
	static List<PKMWeapon*>* getListHammer();
	void deltaUpdate();
	//void onCollision(MGMBox* otherObject, int nx, int ny);
	PKMWeapon();
	~PKMWeapon();
};

