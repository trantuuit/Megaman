#include "MegamanBullet.h"
#include"MGMSpriteManager.h"
#include "BonusBall.h"
#include "LifeEnergyBig.h"
#include "LifeEnergySmall.h"
#include "WeaponEnergyBig.h"
#include "WeaponEnergySmall.h"
#include "Up.h"
#include "Yashichi.h"
#include <stdlib.h>
#include <time.h>
#include "MGMEnemy.h"
#include"Megaman.h"
List<MegamanBullet*>* MegamanBullet::bullets = 0;
List<MegamanBullet*>* MegamanBullet::getListBullet()
{
	if (bullets == 0)
		bullets = new List<MegamanBullet*>();
	return bullets;
}

MegamanBullet::MegamanBullet()
{
	this->width = 7;
	this->height = 6;
	collisionCategory = CC_MEGAMAN_BULLET;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_BULLET];
	curAction = 0;
	curFrame = 0;
	timedelay.init(100);
	action = NORMAL;
	getListBullet()->_Add(this);
}
void MegamanBullet::update(){
	/*MGMMovableObject::updateFrameAnimation();*/
}
void MegamanBullet::onCollision(MGMBox* otherObject, int nx, int ny){

}
void MegamanBullet::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_ENEMY){
		MGMEnemy* enemy = (MGMEnemy*)otherObject;
		if (enemy->categoryEnemy != ROOM){
			dx = 0;
			dy = 0;
			isKill = true;
		}
	}
}
void MegamanBullet::setAction(MEGAMANBULLET_ACTION action){
	this->action = action;
}
MegamanBullet::~MegamanBullet()
{
}
