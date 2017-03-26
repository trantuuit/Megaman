#pragma once
#include"MGMBox.h"
#include"MGMSprite.h"
class MGMObject : public MGMBox
{
public:
	Direction objectDirection;
	MGMSprite* sprite;
	MGMGameTime timeFrame;
	int curAction;
	int curFrame;
	
	MGMRectangle oldRect;
	
	void init(float x, float y, float width, float height);

	//khoi phuc lai vi tri object
	virtual void restoreObject();
	
	virtual void setCurAction(int curAction);
	void onCollision(MGMBox* other, int nx, int ny);

	virtual void onLastFrameAnimation(int action);

	void update();
	void render();
	MGMObject();
	~MGMObject();
};

