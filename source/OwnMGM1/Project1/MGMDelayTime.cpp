#include "MGMDelayTime.h"


void MGMDelayTime::start(DWORD time)
{
	ready = false;
	terminated = false;
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
	terminated = false;
}

bool MGMDelayTime::isReady()
{
	return ready;
}
bool MGMDelayTime::isTerminated()
{
	if (terminated)
	{
		ready = true;
		terminated = false;
		return true;
	}
	return false;
}
bool MGMDelayTime::isOnTime()
{
	return !terminated && !ready;
}
void MGMDelayTime::update()
{
	DWORD now = GetTickCount();
	DWORD deltaTime = now - startTime;
	if (deltaTime >= tickPerFrame)
	{
		terminated = true;
	}
}

MGMDelayTime::~MGMDelayTime()
{
}
