#include "MGMGameTime.h"


MGMGameTime::MGMGameTime(void)
{
}

void MGMGameTime::start()
{
	startTime = GetTickCount();
}

MGMGameTime::MGMGameTime(DWORD tickPerFrame)
{
	this->tickPerFrame = tickPerFrame;
}


bool MGMGameTime::atTime()
{

	DWORD now = GetTickCount();
	deltaTime = now - startTime;

	if (deltaTime >= tickPerFrame)
	{
		startTime = GetTickCount();
		return true;
	}
	return false;
}

MGMGameTime::~MGMGameTime(void)
{
}
