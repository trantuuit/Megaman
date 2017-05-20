#include "EnemyBullet.h"


List<EnemyBullet*>* EnemyBullet::bullets = 0;
List<EnemyBullet*>* EnemyBullet::getListBullet()
{
	if (bullets == 0)
		bullets = new List<EnemyBullet*>();
	return bullets;
}

EnemyBullet::EnemyBullet()
{
	this->collisionCategory = CC_ENEMY_BULLET;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_BEAK_BULLET];
	getListBullet()->_Add(this);
}
void EnemyBullet::onCollision(MGMBox* otherObject, int nx, int ny){
	if (otherObject->collisionCategory == CC_MEGAMAN){
		isKill = true;
		/*vy = objectDirection*vy;*/
		/*if (ny == 1){
			vy = -vy;
		}*/
	}
}
EnemyBullet::~EnemyBullet()
{
}
