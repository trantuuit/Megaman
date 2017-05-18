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
	timeDie.init(4000);
	vx = 0;
	vy = 0.6;
	collisionCategory = CC_ITEM;
}
void MGMItem::onInterserct(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN){
		isKill = true;
	}
}
void MGMItem::onCollision(MGMBox* otherObject, int nx, int ny){
	if (otherObject->collisionCategory == CC_GROUND){
		Collision::preventMove(this, otherObject,nx, ny);
		vx = 0;
	}
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		vy = 1;
	}
}
void MGMItem::update(){
	MGMMovableObject::update();
	CountDownDie();
}
void MGMItem::CountDownDie(){
	if (timeDie.isReady()){
		timeDie.start();
	}
	if (!timeDie.isOnTime()){
		isKill = true;
	}
	timeDie.update();
}
MGMItem::~MGMItem()
{
}
