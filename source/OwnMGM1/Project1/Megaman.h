﻿#pragma once
#include "MGMMovableObject.h"
#include "MGMDelayTime.h"

enum MEGAMAN_ACTION
{
	MGM_STAND,
	MGM_PRE_RUN,
	MGM_RUN,
	MGM_JUMP,
	MGM_CLIMB,
	MGM_STAND_ATTACK,
	MGM_RUN_ATTACK,
	MGM_JUMP_ATTACK,
	MGM_STAND_STAIR_ATTACK,
};

class Megaman :
	public MGMMovableObject
{
	int life;
	
public:
	int healthPoint;
	void setHealth(int health);
	MGMDelayTime eyesTime;
	//MGMDelayTime eyesTime2;
	MGMDelayTime delayAnimateStandShoot;
	MGMDelayTime delayAnimateRunShoot;
	MGMDelayTime delayAnimateJumpShoot;
	MGMDelayTime delayAnimateStandStairShoot;
	MGMDelayTime delayShoot;

	//MGMDelayTime timeStand, timeGo;

	bool isOnStairs;
	int IntersectDoor;
	static Megaman* instance;
	static Megaman* getInstance();
	
	int action;
	bool lastStatusStandStairAttack;
	bool lastStatusStandAttack;
	bool lastStatusRunAttack;
	bool lastStatusJumpAttack;
	bool pauseAnimation;

	/*Cập nhật*/
	void update();
	void render();

	void setCurAction(int action);
	void onInterserct(MGMBox* otherObject);

	void onLastFrameAnimation(int action);
	void updateFrameAnimation();

	void setWidth(int width);


	void onCollision(MGMBox* otherObject, int nx, int ny);

	Megaman();
	~Megaman();
};

