#include "Yashichi.h"
#include "MGMSpriteManager.h"

Yashichi::Yashichi()
{
	categoryItem = CI_YASHICHI;
	this->width = this->height = 16;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_YASHICHI];
	getListItem()->_Add(this);
}


Yashichi::~Yashichi()
{
}
