#pragma once
#include"MGMBox.h"
#include"MGMSprite.h"

//Dung: Thêm enum để vẽ khi map rung:
enum DRAW_LOCATION
{
	DRAW_LOCATION_1,
	DRAW_LOCATION_2,
	DRAW_LOCATION_3,
	DRAW_LOCATION_4,
	DRAW_LOCATION_5,
	DRAW_LOCATION_6
};
class MGMObject : public MGMBox
{
private:
	
public:
	DRAW_LOCATION drawLocation;
	int drawPerLocation; // Đếm số lần render tại 1 Location khi rung
	const int drawCount = 1; // Giới hạn maximum cho số lần render tại 1 Location khi rung

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
	virtual void vibrateRender(); //Dung: Hàm render rung map
	MGMObject();
	~MGMObject();
};

