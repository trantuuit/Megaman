#include "CutmanRoom.h"
#include"BossCutMan.h"


CutmanRoom::CutmanRoom()
{
	ax = 0;
	vx = 0;
	ay = 0;
	vy = 0;
	objectDirection = LEFT;
	ActionCount = 0;
}

void CutmanRoom::update()
{
	if (ActionCount <= 80) // Update Frame đủ 80 lần
	{
		BossCutMan::getInstance()->appearMusic = true;
		MGMMovableObject::update();
		ActionCount++;
	}
	else{
		curFrame = 1;
		BossCutMan::getInstance()->appearHP = true;
	}
		
}

void CutmanRoom::render()
{
	MGMMovableObject::render();
}


CutmanRoom::~CutmanRoom()
{
}
