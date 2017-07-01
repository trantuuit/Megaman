#pragma once
#include<Windows.h>
/**/
class MGMGameTime
{
public:
	MGMGameTime();
	~MGMGameTime();
	DWORD _timeStart;
	DWORD _tickPerFrame;
	DWORD _timeDelta;
	MGMGameTime(DWORD tickPerFrame);
	//Điều kiện để delta time (giữa 2 frame) > tickPerFrame
	virtual bool at(); 
	//Lấy thời điểm bắt đầu ở hiện tại ( get tick count)
	virtual void start();  
};

