#include "MGMGameTime.h"


MGMGameTime::MGMGameTime()
{
}
MGMGameTime::~MGMGameTime()
{
}
void MGMGameTime::start()
{
	_timeStart = GetTickCount();
}
MGMGameTime::MGMGameTime(DWORD tickPerFrame)
{
	this->_tickPerFrame = tickPerFrame;
}
bool MGMGameTime::at()
{

	DWORD now = GetTickCount();
	_timeDelta = now - _timeStart;

	if (_timeDelta >= _tickPerFrame)
	{
		_timeStart = GetTickCount();
		return true;
	}
	return false;
}