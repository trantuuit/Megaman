#include "PicketMan.h"



void PicketMan::update()
{
	MGMEnemy::update();
}

void PicketMan::render()
{
	MGMEnemy::render();
}

PicketMan::PicketMan()
{
	curAction = 1;
	curFrame = 0;
}


PicketMan::~PicketMan()
{
}
