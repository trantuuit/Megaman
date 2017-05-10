#include "SuperCutter.h"
#include "Megaman.h"

Location SuperCutter::location = LOCATION_1;
MGMDelayTime SuperCutter::timeDelay = MGMDelayTime();
List<SuperCutter*>* SuperCutter::superCutters = 0;

bool SuperCutter::isAppear()
{
	if (Megaman::getInstance()->x >= 845 && Megaman::getInstance()->x <= 961 && Megaman::getInstance()->y > 1000)
	{
		location = LOCATION_1;
		return true;
	}
	if (Megaman::getInstance()->x >= 1360 && Megaman::getInstance()->x <= 1476 && Megaman::getInstance()->y > 1950)
	{
		location = LOCATION_2;
		return true;
	}
	return false;
}
List<SuperCutter*>* SuperCutter::getSuperCutters()
{
	if (superCutters == 0)
		superCutters = new List<SuperCutter*>();
	return superCutters;
}
SuperCutter::SuperCutter()
{
	curAction = 0;
	curFrame = 0;
	ay = GRAVITY;
	//vx = -0.25;
	vy = 0.78;
	//timeFrame.tickPerFrame = 300;

	sprite = MGMSpriteManager::getInstance()->sprites[SPR_SUPER_CUTTER];
	getSuperCutters()->_Add(this);
}

SuperCutter::SuperCutter(int x, int y, int w, int h)
{
	MGMObject::init(x, y, w, h);
	SuperCutter();
}

void SuperCutter::updateMove()
{
	vx = vx + ax * GAMETIME;
	dx = vx * GAMETIME;

	vy = vy + ay * GAMETIME;
	dy = vy * GAMETIME;
}

void SuperCutter::updateLocation()
{
	if (isCollision && !isChangeDelta)
	{
		dy = 0;
	}
	x += dx;
	y += dy;
}


SuperCutter::~SuperCutter()
{

}
