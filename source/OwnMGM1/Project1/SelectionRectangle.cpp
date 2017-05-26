#include "SelectionRectangle.h"
#include"KEY.h"
#include"MGMGame.h"

void SelectionRectangle::update()
{
	if (KEY::getInstance()->isMovePress)
	{
		if (x == 55)
		{
			x = 153;
			boss = GutsMan;
		}
		else if (x == 153)
		{
			x = 55;
			boss = CutMan;
		}

	}
	this->updateFrameAnimation();
	if (KEY::getInstance()->isEnterPress)
	{
		MGMGame::getInstance()->isStart = false;
		if (boss == CutMan)
			MGMGame::getInstance()->map = MGMGame::getInstance()->mapCut;
		else
			MGMGame::getInstance()->map = MGMGame::getInstance()->mapGut;
	}
}

void SelectionRectangle::render()
{
	this->sprite->Render(x, y, curAction, curFrame);
}

SelectionRectangle::SelectionRectangle()
{
	this->sprite= new MGMSprite("Data\\Animation\\Selection Rectangle\\SelectionRectangle.txt", "Data\\Animation\\Selection Rectangle\\SelectionRectangle.png");
	x = 55;
	y = 80;
	boss = CutMan;
}


SelectionRectangle::~SelectionRectangle()
{
}
