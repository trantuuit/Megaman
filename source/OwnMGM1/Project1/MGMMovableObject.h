#pragma once
#include "MGMObject.h"
class MGMMovableObject :
	public MGMObject
{
public:
	MGMRectangle spaceMove;
	virtual void updateMove();
	virtual void update();
	MGMMovableObject();
	~MGMMovableObject();
};

