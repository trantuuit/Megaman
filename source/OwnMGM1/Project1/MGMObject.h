#pragma once
#include"MGMBox.h"
#include"MGMSprite.h"
class MGMObject : public MGMBox
{
public:
	Direction objectDirection;
	int id;
	boolean isKill;
	MGMSprite* sprite;
	MGMGameTime timeFrame;
	bool isOnGround;
	int curAction;
	int curFrame;
	
	MGMRectangle oldRect;
	
	void init(float x, float y, float width, float height);

	//khoi phuc lai vi tri object
	virtual void restoreObject();
	
	virtual void setCurAction(int curAction);
	virtual	void onCollision(MGMBox* otherObject, int nx, int ny);

	virtual void onLastFrameAnimation(int action);

	void update();
	virtual void updateFrameAnimation();
	virtual void render();
	MGMObject();
	~MGMObject();
};

