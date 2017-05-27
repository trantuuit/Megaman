#include "StoneDead.h"
#include"EnemyBullet.h"

StoneDead::StoneDead()
{
	categoryEnemy = DEATH_LAND;
	dx = 0;
	dy = 0;
	ax = 0;
	ay = 0;
	vx = 0;
	vy = 0;
}
void StoneDead::onIntersectRect(MGMBox* otherObject){
	
}

StoneDead::~StoneDead()
{
}
