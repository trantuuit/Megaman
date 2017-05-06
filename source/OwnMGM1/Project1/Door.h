#pragma once
#include "MGMObject.h"
#include"List.h"
class Door :
	public MGMObject
{
public:
	bool pauseAnimation;
	bool isClosed;
	bool isOpened;
	Door();
	void Open();
	void Close();
	void updateFrameAnimation();
	void onLastFrameAnimation(int curAction);
	Door(int x, int y, int w, int h);
	~Door();
};

