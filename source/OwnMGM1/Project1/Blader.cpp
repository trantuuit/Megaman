#include "Blader.h"
#include "Megaman.h"
#include "MGMCamera.h"
Blader::Blader()
{
	curAction = 0;
	curFrame = 0;
	vx = -0.2;
	vy = -0.5;
	ay = 0;
}

void Blader::updateMove(){
	int xM, yM, xB, yB;
	xM = Megaman::getInstance()->x;
	yM = Megaman::getInstance()->y;
	xB = x;
	yB = y;
	float s;
	s = sqrt((xM - xB)*(xM - xB) + (yM - yB)*(yM - yB));
	if (s <= 100){
		vx = vx + ax*GAMETIME;
		dx = (int)(vx*GAMETIME);
		dy = (int)(vy*GAMETIME);
	}
	else{
		vx = vx + ax*GAMETIME;
		dx = (int)(vx*GAMETIME);
	}

	/*dy = abs(dx);*/
	/*Megaman::getInstance()->dx;*/
	//vy = vy + ay*GAMETIME;
	//dy = (vy*GAMETIME);
}

void Blader::update()
{
	//if (MGMCamera::getInstance()->dx > 0){
	//	vx = -0.2;
	//}
	//else{
	//	vx = 0.2;
	//}
	MGMEnemy::update();
	MGMEnemy::updateFrameAnimation();
	updateMove();
}

void Blader::render(){
	MGMEnemy::render();
}
void Blader::onCollision(MGMBox* other, int nx, int ny){
	/*MGMEnemy::onCollision(other, nx, ny);*/
	//if (other->collisionCategory == CC_GROUND)
	//{
	//	if (nx != 0)
	//		vx = abs(vx)*nx;
	//}
	//if (other == Megaman::getInstance())
	//{
	//	Collision::preventMove(Megaman::getInstance(), this);
	//}
}


Blader::~Blader()
{
}
