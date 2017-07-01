#pragma once
#include<Windows.h>
class MGMDelayTime
{
private:
	DWORD _start;
	DWORD tickPerFrame;
	bool ready, finished;
public:
	void start(DWORD time = -1);
	bool isReady();
	bool isFinish();
	bool isSchedule();
	void update();
	void init(DWORD time = -1);
	MGMDelayTime();
	~MGMDelayTime();
};

