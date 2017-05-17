#include "BigEye.h"
#include "Megaman.h"
#include <stdlib.h>
#include <time.h>



BigEye::BigEye()
{
	vx = -0.3;
	//vy = 0.85;
	ay = GRAVITY;
	activity = BIGEYE_STAND;
	delayBeforeJump.init(500);
	delayBeforeJump.start(500);

}

void BigEye::onCollision(MGMBox * other, int nx, int ny)
{
	if (ny == 1)
	{
		activity = BIGEYE_STAND;
		delayBeforeJump.start();
	}
	MGMMovableObject::onCollision(other, nx, ny);
	if (other->collisionCategory == CC_MEGAMAN_BULLET){
		isKill = true;
	}
}

void BigEye::update()
{
	switch (activity)
	{
	case BIGEYE_STAND:
		vx = 0;
		vy = 0;
		ay = 0;
		curFrame = 0;
		if (delayBeforeJump.isTerminated())
		{
			objectDirection = (Megaman::getInstance()->getXCenter() < this->getXCenter()) ? LEFT : RIGHT;
			curFrame = 1;
			vx = 0.33 * objectDirection;
			vy = ramdomVy() == 0 ? 0.67 : 0.95;
			ay = GRAVITY;
			activity = BIGEYE_JUMP;
		}
		break;
	case BIGEYE_JUMP:
		break;
	default:
		break;
	}
	delayBeforeJump.update();

	MGMMovableObject::updateMove();
	//MGMBox::update();
}

void BigEye::render()
{
	MGMEnemy::render();
}

int BigEye::ramdomVy()
{
	srand(time(NULL));
	int result = rand() % 2;
	return result;
}


BigEye::~BigEye()
{
}
