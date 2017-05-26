#pragma once
#include"MGMEnemy.h"
#include"List.h"

class PKMWeapon: public MGMEnemy
{
public:
	static List<PKMWeapon*>* hammer;
	static List<PKMWeapon*>* getListHammer();
	void deltaUpdate();
	//void onCollision(MGMBox* otherObject, int nx, int ny);
	PKMWeapon();
	~PKMWeapon();
};

