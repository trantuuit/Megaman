#include "MGMEnemy.h"



MGMEnemy::MGMEnemy()
{
	vy = 0.5;
	collisionCategory = CC_ENEMY;
	isKill = false;
	count = 0;
}


MGMEnemy::~MGMEnemy()
{
}
