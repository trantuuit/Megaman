#pragma once
#include<Windows.h>
class MGMDelayTime
{
private:
	DWORD startTime;
	DWORD tickPerFrame;
	bool ready, terminated;
public:
	void start(DWORD time = -1);
	bool isReady();
	bool isTerminated();
	bool isOnTime();
	void update();
	void init(DWORD time = -1);
	MGMDelayTime();
	~MGMDelayTime();
};

