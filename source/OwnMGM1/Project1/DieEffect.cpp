#include "DieEffect.h"
#include"MGMSpriteManager.h"
List<DieAffect*>* DieAffect::list = 0;
List<DieAffect*>* DieAffect::getList()
{
	if (list == 0)
		list = new List<DieAffect*>();
	return list;
}
DieAffect::DieAffect(){

}

DieAffect::DieAffect(AFFECT_CATEGORY category)
{
	if(category == MEGAMAN_DIE){
		sprite = MGMSpriteManager::getInstance()->sprites[SPR_DIE_AFFECT];
		curAction = 0;
	}
	else if (category == CUTMAN_DIE){
		sprite = MGMSpriteManager::getInstance()->sprites[SPR_DIE_AFFECT];
		curAction = 1;
	}
	else if (category == GUTMAN_DIE){
		sprite = MGMSpriteManager::getInstance()->sprites[SPR_DIE_AFFECT];
		curAction = 2;
	}
	vy = 0;
	vx = 0;
	ax = 0;
	ay = 0;
	this->collisionCategory = CC_NONE_CATEGORY;
	getList()->_Add(this);
}


DieAffect::~DieAffect()
{
}
