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
List<MegamanBullet*>* MegamanBullet::bullets = 0;
List<MegamanBullet*>* MegamanBullet::getBullets()
{
	if (bullets == 0)
		bullets = new List<MegamanBullet*>();
	return bullets;
}

MegamanBullet::MegamanBullet()
{
	this->width = this->height = 8;
	collisionCategory = CC_MEGAMAN_BULLET;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_BULLET];
	curAction = 0;
	curFrame = 0;
	timedelay.init(100);
	action = NONE;
	getBullets()->_Add(this);
}
void MegamanBullet::update(){
	if (action == FIRE){
		if (timedelay.isReady()){
			timedelay.start();
		}
		if (timedelay.isOnTime()){
			curAction = 1;
			/*curFrame = 0;*/
		}
		else{
			isKill = true;
		}
		timedelay.update();
	}
	MGMMovableObject::updateFrameAnimation();

}
void MegamanBullet::onCollision(MGMBox* other, int nx, int ny){
	if (other->collisionCategory == CC_ENEMY){
		dx = 0;
		dy = 0;
		action = FIRE;
		/*isKill = true;*/
		srand(time(NULL));
		int result = rand() % 7;

		if (result == 0){
			LifeEnergyBig* lifeEnergyBig = new LifeEnergyBig();
			lifeEnergyBig->x = this->x;
			lifeEnergyBig->y = this->y;
		}
		if (result == 1){
			BonusBall* bonusball = new BonusBall();
			bonusball->x = this->x;
			bonusball->y = this->y;
		}
		if (result == 2){
			LifeEnergySmall* lifeEnergySmall = new LifeEnergySmall();
			lifeEnergySmall->x = this->x;
			lifeEnergySmall->y = this->y;
		}
		if (result == 3){
			WeaponEnergyBig* weaponEnergyBig = new WeaponEnergyBig();
			weaponEnergyBig->x = this->x;
			weaponEnergyBig->y = this->y;
		}
		if (result == 4){
			WeaponEnergySmall* weaponEnergySmall = new WeaponEnergySmall();
			weaponEnergySmall->x = this->x;
			weaponEnergySmall->y = this->y;
		}
		if (result == 5){
			Up* up = new Up();
			up->x = this->x;
			up->y = this->y;
		}
		if (result == 6){
			Yashichi* yashichi = new Yashichi();
			yashichi->x = this->x;
			yashichi->y = this->y;
		}

	}
}

MegamanBullet::~MegamanBullet()
{
}
