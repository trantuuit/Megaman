#pragma once
#include"MGMBox.h"
#include"MGMSprite.h"
extern int gameTime;
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
	
	void setCurAction(int curAction);
	void onCollision(MGMBox* other, int nx, int ny);

	void update();
	void render();
	MGMObject();
	~MGMObject();
};

