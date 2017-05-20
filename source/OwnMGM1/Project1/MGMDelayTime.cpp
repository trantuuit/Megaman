#include "MGMDelayTime.h"


void MGMDelayTime::start(DWORD time)
{
	ready = false;
	finished = false;
	startTime = GetTickCount();
	if (time != (DWORD)-1)
	{
		init(time);
	}
}

void MGMDelayTime::init(DWORD time)
{
	tickPerFrame = time;
}

MGMDelayTime::MGMDelayTime()
{
	ready = true;
	finished = false;
}

bool MGMDelayTime::isReady()
{
	return ready;
}
bool MGMDelayTime::isFinish()
{
	if (finished)
	{
		ready = true;
		finished = false;
		return true;
	}
	return false;
}
bool MGMDelayTime::isSchedule()
{
	return !finished && !ready;
}
void MGMDelayTime::update()
{
	DWORD now = GetTickCount();
	DWORD deltaTime = now - startTime;
	if (deltaTime >= tickPerFrame)
	{
		finished = true;
	}
}

MGMDelayTime::~MGMDelayTime()
{
}
