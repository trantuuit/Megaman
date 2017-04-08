#pragma once
#include "MGMMovableObject.h"
#include "MGMDelayTime.h"

enum MEGAMAN_ACTION
{
	MGM_STAND,
	MGM_PRE_RUN,
	MGM_RUN,
	MGM_JUMP,
	MGM_CLIMB,
};

class Megaman :
	public MGMMovableObject
{
public:
	MGMDelayTime eyesTime1;
	MGMDelayTime eyesTime2;
	/*MGMGameTime eyesTime;*/
	MGMDelayTime delayShoot;

	//MGMDelayTime timeStand, timeGo;

	bool isOnStairs;
	static Megaman* instance;
	static Megaman* getInstance();
	
	int action;
	bool pauseAnimation;

	/*Cập nhật vận tốc*/
	void update();
	void render();

	void setCurAction(int action);
	void onInterserct(MGMBox* other);

	void onLastFrameAnimation(int action);
	void updateFrameAnimation();

	void setWidth(int width);


	void onCollision(MGMBox* other, int nx, int ny);

	Megaman();
	~Megaman();
};

