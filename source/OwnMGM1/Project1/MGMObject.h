#pragma once
#include"MGMBox.h"
#include"MGMSprite.h"
class MGMObject : public MGMBox
{
public:
	Direction objectDirection;
	MGMSprite* sprite;
	MGMGameTime timeFrame;
	bool isOnGround;
	int curAction;
	int curFrame;
	bool isUpdateFrameAnimation;
	
	MGMRectangle oldRect;
	
	void init(float x, float y, float width, float height);

	//khoi phuc lai vi tri object
	virtual void restoreObject();
	
	virtual void setCurAction(int curAction);
	virtual	void onCollision(MGMBox* other, int nx, int ny);

	virtual void onLastFrameAnimation(int action);

	void update();
	virtual void updateFrameAnimation();
	void render();
	MGMObject();
	~MGMObject();
};

