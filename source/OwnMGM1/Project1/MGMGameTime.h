#pragma once
#include<Windows.h>
/**/
class MGMGameTime
{
public:
	DWORD startTime;
	DWORD tickPerFrame;
	DWORD deltaTime;
	MGMGameTime(void);
	~MGMGameTime(void);

	MGMGameTime(DWORD tickPerFrame);
	//Điều kiện để delta time (giữa 2 frame) > tickPerFrame
	virtual bool atTime(); 
	//Lấy thời điểm bắt đầu ở hiện tại ( get tick count)
	virtual void start();  

};

