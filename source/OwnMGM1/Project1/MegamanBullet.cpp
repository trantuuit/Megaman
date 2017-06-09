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
#include <math.h>
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
	category_bullet = OF_MEGAMAN;
	getListBullet()->_Add(this);
}
MegamanBullet::MegamanBullet(CATEGORY_BULLET_FOR_MEGAMAN category){
	if (category == OF_MEGAMAN){
		this->width = 7;
		this->height = 6;
		collisionCategory = CC_MEGAMAN_BULLET;
		sprite = MGMSpriteManager::getInstance()->sprites[SPR_BULLET];
		curAction = 0;
		curFrame = 0;
		timedelay.init(100);
		action = NORMAL;
		category_bullet = category;
		getListBullet()->_Add(this);
	}
	else if (category == OF_CUTMAN){
		dx = 0;
		dy = 0;
		vx = 0;
		vy = 0;
		ax = 0;
		ay = 0;
		sprite = MGMSpriteManager::getInstance()->sprites[SPR_CUTMANBULLET];
		t = 0;
		width = 14;
		height = 10;
		category_bullet = OF_CUTMAN;
		curAction = 0;
		curFrame = 0;
		action = IS_THROW;
		x = 0;
		y = 0;
		collisionCategory = CC_MEGAMAN_BULLET;
		isThrowLeft = false;
		isThrowRight = false;
		getListBullet()->_Add(this);
	}
}
void MegamanBullet::update(){
	if (action == IS_THROW){
		objectDirection = Megaman::getInstance()->objectDirection;

		if (Megaman::getInstance()->objectDirection == RIGHT&&!isThrowLeft){
			x0 = Megaman::getInstance()->x + 14;
			y0 = Megaman::getInstance()->y - 2;
			x1 = x0 + 40;
			y1 = y0 + 40;
			x2 = x0 + 130;
			y2 = y0 + 0;
			x3 = x0 + 40;
			y3 = y0 - 40;
			isThrowRight = true;
		}
		if (isThrowRight){
			x0 = Megaman::getInstance()->x + 14;
			y0 = Megaman::getInstance()->y - 2;
			x1 = x0 + 40;
			y1 = y0 + 40;
			x2 = x0 + 130;
			y2 = y0 + 0;
			x3 = x0 + 40;
			y3 = y0 - 40;
		}
		if (Megaman::getInstance()->objectDirection == LEFT&&!isThrowRight){
			x0 = Megaman::getInstance()->x - 11;
			y0 = Megaman::getInstance()->y - 2;
			x1 = x0 - 40;
			y1 = y0 + 40;
			x2 = x0 - 130;
			y2 = y0 + 0;
			x3 = x0 - 40;
			y3 = y0 - 40;
			isThrowLeft = true;
		}
		if (isThrowLeft){
			x0 = Megaman::getInstance()->x - 11;
			y0 = Megaman::getInstance()->y - 2;
			x1 = x0 - 40;
			y1 = y0 + 40;
			x2 = x0 - 130;
			y2 = y0 + 0;
			x3 = x0 - 40;
			y3 = y0 - 40;
		}
		t += 0.017;
		x = (float)pow(1 - t, 4)*x0 + 4 * pow(1 - t, 3)*t*x1 + 6 * pow(1 - t, 2)*t*t*x2 + 4 * (1 - t)*pow(t, 3)*x3 + pow(t, 4)*x0;
		y = (float)pow(1 - t, 4)*y0 + 4 * pow(1 - t, 3)*t*y1 + 6 * pow(1 - t, 2)*t*t*y2 + 4 * (1 - t)*pow(t, 3)*y3 + pow(t, 4)*y0;


		setCurAction(1); //Set action bay cho CutmanBullet
	}
	updateFrameAnimation();
	/*MGMMovableObject::coordinateUpdate();*/

}
void MegamanBullet::onCollision(MGMBox* otherObject, int nx, int ny){

}
void MegamanBullet::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_ENEMY){
		MGMEnemy* enemy = (MGMEnemy*)otherObject;
		if (enemy->categoryEnemy != ROOM && category_bullet == OF_MEGAMAN){
			dx = 0;
			dy = 0;
			isKill = true;
		}
	}
	if (otherObject->collisionCategory == CC_MEGAMAN){
		isKill = true;
		isThrowLeft = false;
		isThrowRight = false;
		t = 0;
	}
}
void MegamanBullet::setAction(MEGAMANBULLET_ACTION action){
	this->action = action;
}
MegamanBullet::~MegamanBullet()
{
}
