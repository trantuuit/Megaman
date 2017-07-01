#pragma once
#include "MGMObject.h"
#include"Collision.h"
class MGMMovableObject :
	public MGMObject
{
public:
	MGMBox spaceMove;
	virtual void deltaUpdate();
	virtual void update();
	virtual	void onCollision(MGMBox* otherObject, int nx, int ny);
	MGMMovableObject();
	~MGMMovableObject();
};

