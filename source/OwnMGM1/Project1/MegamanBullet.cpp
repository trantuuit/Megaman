#include "MegamanBullet.h"
#include"MGMSpriteManager.h"




List<MegamanBullet*>* MegamanBullet::bullets = 0;
List<MegamanBullet*>* MegamanBullet::getBullets()
{
	if (bullets == 0)
		bullets = new List<MegamanBullet*>();
	return bullets;
}

MegamanBullet::MegamanBullet()
{
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_BULLET];
	getBullets()->_Add(this);
}


MegamanBullet::~MegamanBullet()
{
}
