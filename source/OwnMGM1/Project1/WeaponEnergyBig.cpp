#include "WeaponEnergyBig.h"
#include "MGMSpriteManager.h"

WeaponEnergyBig::WeaponEnergyBig()
{
	categoryItem = CI_WEAPON_ENERGY_BIG;
	this->width = 16;
	this->height = 12;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_WEAPON_ENERGY_BIG];
	getListItem()->_Add(this);
}


WeaponEnergyBig::~WeaponEnergyBig()
{
}
