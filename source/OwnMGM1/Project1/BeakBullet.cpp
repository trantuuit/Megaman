#include "BeakBullet.h"


List<BeakBullet*>* BeakBullet::bullets = 0;
List<BeakBullet*>* BeakBullet::getBullets()
{
	if (bullets == 0)
		bullets = new List<BeakBullet*>();
	return bullets;
}

BeakBullet::BeakBullet()
{
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_BEAK_BULLET];
	getBullets()->_Add(this);
}

BeakBullet::~BeakBullet()
{
}
