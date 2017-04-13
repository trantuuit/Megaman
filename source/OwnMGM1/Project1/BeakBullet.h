#pragma once
#include "MGMEnemy.h"
#include "List.h"
#include"MGMSpriteManager.h"
class BeakBullet :
	public MGMEnemy
{
	static List<BeakBullet*>* bullets;
public:
	static List<BeakBullet*>* getBullets();
	BeakBullet();
	~BeakBullet();
};

