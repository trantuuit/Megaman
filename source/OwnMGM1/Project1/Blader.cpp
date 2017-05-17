#include "Blader.h"
#include "Megaman.h"
#include "MGMCamera.h"
Blader::Blader()
{
	curAction = 0;
	curFrame = 0;
	vx = 0;
	vy = 0;
	ay = 0.007;
	detectMegaman = false;
	attack.init(500);
	updateTarget.tickPerFrame=500;
	bladerActivity = BLADER_STEP1;
	objectDirection = Direction::LEFT;
	isKill = false;
}
boolean Blader::checkNearMegaman(){
	float xM, yM, xB, yB;
	xM = Megaman::getInstance()->x;
	yM = Megaman::getInstance()->y;
	xB = x;
	yB = y;
	float distance;
	distance = sqrt((xM - xB)*(xM - xB) + (yM - yB)*(yM - yB));
	if (abs(xM-xB) <= 50){
		if (updateTarget.atTime()){
			xTarget = xM;
			yTarget = yM;
		}
		detectMegaman = true;
		return true;
	}
	else{
		return false;
	}
}

void Blader::attackMegaman(){
	boolean left, right;
	if (attack.isReady()){
		attack.start();
	}

	if(attack.isOnTime()){
		vy = -0.93;
		ay = 0.007;
		if (vx > 0){
			vx = 0.4f;
		}
		else{
			vx = -0.4f;
		}
		if ((y - yTarget) >= 0 ) {
			//if (abs(y - oldRect.y) <= 2){
			//	dy = -3;
			//}
			dy = -3;
		}
		if ((y - yTarget) < 0 ){
			dy = 3;
		}
		if (abs(y - yTarget) <= 3){

		}
		dx = (int)(vx*GAMETIME);

	}
	if (attack.isTerminated()){
		if (vx > 0){
			vx = 0.2f;

		}
		else{
			vx = -0.2f;
		}
		dx = (int)(vx*GAMETIME);
	}
	attack.update();
}

void Blader::stopAttack(){
	dx = (int)(vx*GAMETIME);
}
void Blader::updateMove(){
	
	if ((x < Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) >50)){
		vx = 0.2f;
		objectDirection = Direction::RIGHT;
	}
	if ((x > Megaman::getInstance()->x) && (abs(x - Megaman::getInstance()->x) > 50)){
		vx = -0.2f;
		objectDirection = Direction::LEFT;
	}
	if (checkNearMegaman()){
		switch (bladerActivity)
		{
		case BLADER_STEP1:
			if (!attack.isOnTime()){
				attack.start();
				if (vx > 0){
					vx = 0.4f;
					dx = 3;
				}
				else{
					vx = -0.4f;
					dx = -3;
				}
				if ((y - yTarget) >= 0) {
					dy = -3;
				}
				if ((y - yTarget) < 0){
					dy = 3;
				}
				if (abs(y - yTarget) <= 3){
					bladerActivity = BLADER_STEP2;
				}
				dx = (int)(vx*GAMETIME);
			}
			attack.update();
			break;
		case BLADER_STEP2:
			if (!attack.isOnTime()){
				attack.start();
				if (vx > 0){
					vx = 0.4f;
					dx = 3;
				}
				else{
					vx = -0.4f;
					dx = -3;
				}
				if ((y - oldRect.y) < 0){
					dy = 3;
				}
				if ((y - oldRect.y) > 0){
					dy = -3;
				}
				if (abs(y - oldRect.y) <= 3){
					bladerActivity = BLADER_STEP1;
				}
				dx = (int)(vx*GAMETIME);
			}
			attack.update();
			break;
		default:
			break;
		}
	}
	else{
		stopAttack();
	}
}

void Blader::update()
{
	MGMEnemy::updateFrameAnimation();
	updateMove();
}

void Blader::render(){
	MGMEnemy::render();
}
void Blader::onCollision(MGMBox* other, int nx, int ny){
	if (other->collisionCategory == CC_MEGAMAN_BULLET){
		
		isKill = true;
	}
}


Blader::~Blader()
{
}
