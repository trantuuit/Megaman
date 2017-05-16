#include "MGMItem.h"
#include "Megaman.h"
List<MGMItem*>* MGMItem::listItem = 0;

List<MGMItem*>* MGMItem::getListItem(){
	if (listItem == NULL){
		listItem = new List<MGMItem*>();
	}
	return listItem;
}
MGMItem::MGMItem()
{
	vx = 0;
	collisionCategory = CC_ITEM;
}

void MGMItem::onCollision(MGMBox* other, int nx, int ny){
	if (other->collisionCategory == CC_GROUND){
		Collision::preventMove(this, other,nx, ny);
		vx = 0;
	}
	if (other == Megaman::getInstance()){
		Collision::preventMove(Megaman::getInstance(), this, nx, ny);
	}
}
MGMItem::~MGMItem()
{
}
