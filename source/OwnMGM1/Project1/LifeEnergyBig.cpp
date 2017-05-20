#include "LifeEnergyBig.h"
#include "MGMSpriteManager.h"

LifeEnergyBig::LifeEnergyBig()
{
	categoryItem = CI_LIFE_ENERGY_BIG;
	this->width = 14;
	this->height = 16;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_LIFE_ENERGY_BIG];
	getListItem()->_Add(this);
}


LifeEnergyBig::~LifeEnergyBig()
{
}
