#include "SmallRock.h"
#include "MGMSpriteManager.h"

List<SmallRock*>* SmallRock::smallRocks = 0;

List<SmallRock*>* SmallRock::getSmallRocks()
{
	if (smallRocks == 0)
		smallRocks = new List<SmallRock*>();
	return smallRocks;
}

SmallRock::SmallRock()
{
	ay = 0;
	vy = 0;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_SMALLROCK];
	getSmallRocks()->_Add(this);
}

void SmallRock::init(int x, int y, int w, int h)
{
	MGMObject::init(x, y, w, h);
	//SmallRock();
}

SmallRock::~SmallRock()
{
}
