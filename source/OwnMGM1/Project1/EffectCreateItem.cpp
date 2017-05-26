#include "EffectCreateItem.h"
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
EffectCreateItem* EffectCreateItem::effect = 0;
EffectCreateItem* EffectCreateItem::getInstance(){
	if (effect == 0){
		effect = new EffectCreateItem();
	}
	return effect;
}
EffectCreateItem::EffectCreateItem()
{
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_ITEM_EFFECT];
	action = ACTION_EFFECT_ITEM_NONE;
	timedelay.init(100);
	curAction = 0;
	curFrame = 0;
	enemy = 0;
	isDraw = false;
}
void EffectCreateItem::update(){
	if (enemy != 0){
		switch (action)
		{
		case ACTION_EFFECT_ITEM_FIRE:
			if (timedelay.isReady()&&timedelay.isFinish()){
				timedelay.start(200);
			}
			if (timedelay.isSchedule()){
				curAction = 0;
				isDraw = true;
				x = enemy->x;
				y = enemy->y;
			}
			if (timedelay.isFinish()) {
				srand(time(NULL));
				int result = rand() % 8;
				if (result == 0){
					LifeEnergyBig* lifeEnergyBig = new LifeEnergyBig();
					lifeEnergyBig->x = enemy->x;
					lifeEnergyBig->y = enemy->y;
				}
				if (result == 1){
					BonusBall* bonusball = new BonusBall();
					bonusball->x = enemy->x;
					bonusball->y = enemy->y;
				}
				if (result == 2){
					LifeEnergySmall* lifeEnergySmall = new LifeEnergySmall();
					lifeEnergySmall->x = enemy->x;
					lifeEnergySmall->y = enemy->y;
				}
				if (result == 3){
					WeaponEnergyBig* weaponEnergyBig = new WeaponEnergyBig();
					weaponEnergyBig->x = enemy->x;
					weaponEnergyBig->y = enemy->y;
				}
				if (result == 4){
					WeaponEnergySmall* weaponEnergySmall = new WeaponEnergySmall();
					weaponEnergySmall->x = enemy->x;
					weaponEnergySmall->y = enemy->y;
				}
				if (result == 5){
					Up* up = new Up();
					up->x = enemy->x;
					up->y = enemy->y;
				}
				if (result == 6){
					Yashichi* yashichi = new Yashichi();
					yashichi->x = enemy->x;
					yashichi->y = enemy->y;
				}
				action = ACTION_EFFECT_ITEM_NONE;
			}
			timedelay.update();
			
			break;
		case ACTION_EFFECT_ITEM_NONE:
			enemy = 0;
			isDraw = false;
			break;
		default:
			break;
		}
	}
	MGMObject::updateFrameAnimation();
}
void EffectCreateItem::render(){
	if (isDraw)
		MGMObject::render();
}
EffectCreateItem::~EffectCreateItem()
{
}
