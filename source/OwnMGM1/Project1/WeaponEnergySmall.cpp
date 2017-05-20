#include "WeaponEnergySmall.h"
#include "MGMSpriteManager.h"

WeaponEnergySmall::WeaponEnergySmall()
{
	categoryItem = CI_WEAPON_ENERGY_SMALL;
	this->width = 12;
	this->height = 8;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_WEAPON_ENERGY_SMALL];
	getListItem()->_Add(this);
}


WeaponEnergySmall::~WeaponEnergySmall()
{
}
