#include "BonusBall.h"
#include "MGMSpriteManager.h"

BonusBall::BonusBall()
{
	/*MGMItem();*/
	categoryItem = CI_BONUS_BALL;
	this->width = 8;
	this->height = 8;
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_BONUS_BALL];
	
	getListItem()->_Add(this);
}


BonusBall::~BonusBall()
{
}
