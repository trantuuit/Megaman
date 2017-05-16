#include "LifeEnergySmall.h"
#include "MGMSpriteManager.h"

LifeEnergySmall::LifeEnergySmall()
{
	this->width = 10;
	this->height = 12;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_LIFE_ENERGY_SMALL];
	getListItem()->_Add(this);
}


LifeEnergySmall::~LifeEnergySmall()
{
}
