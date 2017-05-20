#include "Up.h"
#include "MGMSpriteManager.h"

Up::Up()
{
	categoryItem = CI_UP;
	this->width = 16;
	this->height = 15;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_UP];
	getListItem()->_Add(this);
}


Up::~Up()
{
}
