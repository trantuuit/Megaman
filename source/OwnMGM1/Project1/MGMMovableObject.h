#pragma once
#include "MGMObject.h"
#include"Collision.h"
class MGMMovableObject :
	public MGMObject
{
public:
	MGMRectangle spaceMove;
	virtual void movingUpdate();
	virtual void update();
	virtual	void onCollision(MGMBox* otherObject, int nx, int ny);


	MGMMovableObject();
	~MGMMovableObject();
};

