#pragma once
#include "MGMMovableObject.h"
class CutmanRoom :
	public MGMMovableObject
{
private:
	int ActionCount;
public:
	void update();
	void render();
	CutmanRoom();
	~CutmanRoom();
};

