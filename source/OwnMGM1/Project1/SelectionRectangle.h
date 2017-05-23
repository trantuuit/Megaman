#pragma once
#include "MGMObject.h"
enum Boss
{
	CutMan,
	GutsMan
};
class SelectionRectangle :
	public MGMObject
{
public:
	Boss boss;
	void update();
	void render();
	SelectionRectangle();
	~SelectionRectangle();
};

