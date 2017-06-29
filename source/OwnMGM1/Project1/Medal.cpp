#include "Medal.h"
#include "MGMSpriteManager.h"


Medal::Medal()
{
	vy = 0;
	ay = -0.001;
	categoryItem = CI_MEDAL;
	this->width = this->height = 16;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_MEDAL];
	getListItem()->_Add(this);
}


Medal::~Medal()
{
}
