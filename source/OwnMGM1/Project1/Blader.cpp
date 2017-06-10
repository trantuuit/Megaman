#include "Blader.h"
#include "Megaman.h"
#include "MGMCamera.h"
#include "MegamanBullet.h"
#include"EffectCreateItem.h"
#include"MGMAudioManager.h"
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
	if ((x < Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) >60)){
		isRight = false;
		isLeft = true;
		isCheck = false;
		objectDirection = Direction::RIGHT;
		t = 0;
	}

	if ((x > Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) > 60)){
		/*vx = -0.2f;*/
		isLeft = false;
		isRight = true;
		objectDirection = Direction::LEFT;
		isCheck = false;
		t = 0;
	}
	
	if (isRight){
		x0mg = Megaman::getInstance()->x;
		y0mg = Megaman::getInstance()->y-30;
		xenemy = x;
		yenemy = y;
		//if (Megaman::getInstance()->x < x2){
		//	x2 = 2 * Megaman::getInstance()->x - xenemy;
		//	y2 = yenemy;
		//}
		if (t==0){
			x2 = 2 * x0mg - xenemy;
			y2 = yenemy;
			isCheck = true;
			x3 = x;
			y3 = y;
		}
		//if (Megaman::getInstance()->x < x2){
		//	x3 = x3 - abs(x0mg - x3);
		//	x2 = 2 * x0mg - x3;
		//	y2 = y3;
		//}
		t += 0.02;
		//x = (float)pow(1 - t, 4)*x3 + 4 * pow(1 - t, 3)*t*x0mg + 6 * pow(1 - t, 2)*t*t*x2 + 4 * (1 - t)*pow(t, 3)*x0mg + pow(t, 4)*x3;
		//y = (float)pow(1 - t, 4)*y3 + 4 * pow(1 - t, 3)*t*y0mg + 6 * pow(1 - t, 2)*t*t*y2 + 4 * (1 - t)*pow(t, 3)*y0mg + pow(t, 4)*y3;
		x = pow(1 - t, 2)*x3 + 2 * (1 - t)*t*x0mg + t*t*x2;
		y = pow(1 - t, 2)*y3 + 2 * (1 - t)*t*y0mg + t*t*y2;
	}
	if (isLeft){
		x0mg = Megaman::getInstance()->x;
		y0mg = Megaman::getInstance()->y-30;
		xenemy = x;
		yenemy = y;

		if (t==0){
			x2 = 2 * x0mg - x;
			y2 = y;
			isCheck = true;
			x3 = x;
			y3 = y;
		}
		//if (Megaman::getInstance()->x > x2){
		//	x3 = x3 + abs(x0mg - x3);
		//	x2 = 2 * x0mg- x3;
		//	y2 = y3;
		//}
		t += 0.02;
		//x = (float)pow(1 - t, 4)*x3 + 4 * pow(1 - t, 3)*t*x0mg + 6 * pow(1 - t, 2)*t*t*x2 + 4 * (1 - t)*pow(t, 3)*x0mg + pow(t, 4)*x3;
		//y = (float)pow(1 - t, 4)*y3 + 4 * pow(1 - t, 3)*t*y0mg + 6 * pow(1 - t, 2)*t*t*y2 + 4 * (1 - t)*pow(t, 3)*y0mg + pow(t, 4)*y3;
		x = pow(1 - t, 2)*x3 + 2 * (1 - t)*t*x0mg + t*t*x2;
		y = pow(1 - t, 2)*y3 + 2 * (1 - t)*t*y0mg + t*t*y2;
	}

	MGMEnemy::updateFrameAnimation();
	MGMEnemy::deltaUpdate();
}

void Blader::render(){
	MGMEnemy::render();
}
void Blader::onCollision(MGMBox* otherObject, int nx, int ny){

}
void Blader::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){

		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		//mgmbullet->x = this->x;
		//mgmbullet->y = this->y;
		/*mgmbullet->setAction(FIRE);*/
		isKill = true;
		Megaman::getInstance()->score += 500;
		EffectCreateItem::getInstance()->enemy = this;
		EffectCreateItem::getInstance()->action = ACTION_EFFECT_ITEM_FIRE;

	}
}


Blader::~Blader()
{
}
