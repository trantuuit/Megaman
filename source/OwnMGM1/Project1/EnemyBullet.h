#pragma once
#include "MGMEnemy.h"
#include "List.h"
#include"MGMSpriteManager.h"
enum CATEGORY_BULLET{
	FOR_BEAK,
	FOR_FLYING_SHELL,
	FOR_SCREW_BOMBER,
	FOR_MET,
	FOR_PKM,
};
class EnemyBullet :
	public MGMEnemy
{
	static List<EnemyBullet*>* bullets;
public:
	CATEGORY_BULLET categoryBullet;
	static List<EnemyBullet*>* getListBullet();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	EnemyBullet();
	~EnemyBullet();
};

