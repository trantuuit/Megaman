#pragma once
#include "MGMMovableObject.h"
#include "MGMDelayTime.h"
enum MEGAMAN_STATUS{
	MEGAMAN_NORMAL,
	MEGAMAN_BE_ATTACKED,
};
enum MEGAMAN_BEING_ATTACKED{
	ATTACKED_NONE,
	STEP1,
	STEP2,
	STEP3,
	STEP4,
};
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
	MGM_EFFECT_BE_ATTACKED1,
	MGM_EFFECT_BE_ATTACKED2,
	MGM_EFFECT_BE_ATTACKED3,
	MGM_EFFECT_BE_ATTACKED4,
};

class Megaman :
	public MGMMovableObject
{
private:
	
public:
	Direction collisionDirection;
	MEGAMAN_STATUS status;
	boolean beingAttacked;
	MEGAMAN_BEING_ATTACKED actionBeingAttacked;
	MGMDelayTime step1, step2, step3, step4;
	int life;
	int healthPoint;
	int score;
	MGMGameTime timeFrame1, timeFrame2;
	MGMDelayTime eyesTime1, eyesTime2;
	MGMDelayTime delayAnimateStandShoot;
	MGMDelayTime delayAnimateRunShoot;
	MGMDelayTime delayAnimateJumpShoot;
	MGMDelayTime delayAnimateStandStairShoot;
	MGMDelayTime delayShoot;
	float dxGreenBar;
	Direction greenBarObjectDirection;
	bool isOnStairs;
	bool isOnGreenBar; // Dung: kiểm tra lúc đứng trên GreenBar
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
	void onIntersectRect(MGMBox* otherObject);
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void onLastFrameAnimation(int action);
	void deltaUpdate();
	void updateFrameAnimation();
	void setWidth(int width);
	Megaman();
	~Megaman();
};

