#include "Blader.h"
#include "Megaman.h"
#include "MGMCamera.h"
#include "MegamanBullet.h"
#include"EffectCreateItem.h"
#include"MGMAudioManager.h"
#include"KEY.h"
Blader::Blader()
{
	curAction = 0;
	curFrame = 0;
	vx = 0;
	vy = 0;
	ay = 0;
	ax = 0;
	objectDirection = Direction::LEFT;
	isKill = false;
	categoryEnemy = CREP_BLADER;
	t = 0;
	isCheck = false;
	isLeft = false;
	isRight = true;
}


void Blader::update()
{
	bool flat1, flat2, flat3, isAboveMG;
	flat1 = flat2 = flat3 = isAboveMG = false;
	if ((x < Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) >55)){
		x += 1;
		MGMEnemy::updateFrameAnimation();
		return;
	}
	if ((x > Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) > 55)){
		x -= 1;
		MGMEnemy::updateFrameAnimation();
		return;
	}

	if ((x < Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) >50)){
		isRight = false;
		isLeft = true;
		isCheck = false;
		objectDirection = Direction::RIGHT;
		t = 0;
		if (y > Megaman::getInstance()->y){
			isAboveMG = true;
		}
		else{
			isAboveMG = false;
		}
		if (abs(y - Megaman::getInstance()->y) < 30){
			flat1 = true;
			flat2 = false;
			flat3 = false;
		}
		else if (abs(y - Megaman::getInstance()->y) > 30 && abs(y - Megaman::getInstance()->y) < 60){
			flat1 = false;
			flat2 = true;
			flat3 = false;
		}
		else{
			flat1 = false;
			flat2 = false;
			flat3 = true;
		}
	}

	if ((x > Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) > 50)){
		isLeft = false;
		isRight = true;
		objectDirection = Direction::LEFT;
		isCheck = false;
		t = 0;
		if (y > Megaman::getInstance()->y){
			isAboveMG = true;
		}
		else{
			isAboveMG = false;
		}
		if (abs(y - Megaman::getInstance()->y) < 30){
			flat1 = true;
			flat2 = false;
			flat3 = false;
		}
		else if (abs(y - Megaman::getInstance()->y) > 30 && abs(y - Megaman::getInstance()->y) < 60){
			flat1 = false;
			flat2 = true;
			flat3 = false;
		}
		else{
			flat1 = false;
			flat2 = false;
			flat3 = true;
		}
	}

	if (isRight || isLeft){
		if (isLeft){
			if ((x > Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) < 55)){
				if (abs(y2 - y) <3){
					x += 3;
				}
				else{
					t += 0.0125;
					x = pow(1 - t, 2)*x3 + 2 * (1 - t)*t*x0mg + t*t*x2;
					y = pow(1 - t, 2)*y3 + 2 * (1 - t)*t*y0mg + t*t*y2;
				}	
				MGMEnemy::updateFrameAnimation();
				return;
			}
		}
		if (isRight){
			if ((x < Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) < 55)){
				if (abs(y2 - y) <3){
					x -= 3;
				}
				else{
					t += 0.0125;
					y = pow(1 - t, 2)*y3 + 2 * (1 - t)*t*y0mg + t*t*y2;
					x = pow(1 - t, 2)*x3 + 2 * (1 - t)*t*x0mg + t*t*x2;
				}	
				MGMEnemy::updateFrameAnimation();
				return;
			}
		}
		x0mg = Megaman::getInstance()->x;
		if (flat1){
			if (isAboveMG){
				y0mg = Megaman::getInstance()->y - 10;
			}
			else{
				y0mg = Megaman::getInstance()->y + 10;
			}

		}
		if (flat2){
			if (isAboveMG){
				y0mg = Megaman::getInstance()->y - 50;
			}
			else{
				y0mg = Megaman::getInstance()->y + 50;
			}
		}
		if (flat3){
			if (isAboveMG){
				y0mg = Megaman::getInstance()->y - 90;
			}
			else{
				y0mg = Megaman::getInstance()->y + 90;
			}
		}

		if (t == 0){
			x2 = 2 * x0mg - x;
			y2 = y;
			x3 = x;
			y3 = y;
		}

		t += 0.025;
		x = pow(1 - t, 2)*x3 + 2 * (1 - t)*t*x0mg + t*t*x2;
		y = pow(1 - t, 2)*y3 + 2 * (1 - t)*t*y0mg + t*t*y2;
	}
	MGMEnemy::updateFrameAnimation();
}

void Blader::render(){
	MGMEnemy::render();
}
void Blader::onCollision(MGMBox* otherObject, int nx, int ny){

}
void Blader::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		isKill = true;
		Megaman::getInstance()->score += 500;
		EffectCreateItem::getInstance()->enemy = this;
		EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;

	}
}


Blader::~Blader()
{
}
