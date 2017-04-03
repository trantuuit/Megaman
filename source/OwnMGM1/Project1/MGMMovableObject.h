#pragma once
#include "MGMObject.h"
#include"Collision.h"
class MGMMovableObject :
	public MGMObject
{
public:
	MGMRectangle spaceMove;
	virtual void updateMove();
	virtual void update();
	virtual	void onCollision(MGMBox* other, int nx, int ny);


	MGMMovableObject();
	~MGMMovableObject();
};

