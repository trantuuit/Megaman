#include "PKMWeapon.h"
#include"MGMSpriteManager.h"
#include"Megaman.h"


List<PKMWeapon*>* PKMWeapon::hammer = 0;
List<PKMWeapon*>* PKMWeapon::getListHammer()
{
	if (hammer == 0)
		hammer = new List<PKMWeapon*>();
	return hammer;
}

void PKMWeapon::deltaUpdate()
{
	vy = vy + ay*GAMETIME;
	dy = (vy*GAMETIME);
}

PKMWeapon::PKMWeapon()
{
	this->collisionCategory = CC_ENEMY_BULLET;
	this->categoryEnemy = PKM_WEAPON;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_PKM_WEAPON];
	categoryBullet = FOR_PKM;
	getListHammer()->_Add(this);
	this->width = this->height = 12;
}

void PKMWeapon::onIntersectRect(MGMBox* otherObject)
{
	
}
PKMWeapon::~PKMWeapon()
{
}
