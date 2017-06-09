#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"
#include "CutmanBullet.h"
enum CUTMAN_ACTION
{
	CM_CLAP,
	CM_JUMP,
	CM_RUN,
	CM_ATTACK,
	CM_IS_DAMAGED
};
enum FRAME_TYPE
{
	HEIGHT_32,
	HEIGHT_24
};
class CutMan :
	public MGMEnemy
{
private:
	static CutMan* cutman;
	bool isJumping;
	bool pauseAnimation;
	bool isSaveVy; // Đã lưu vy trước khi attack
	float vyBeforeAttack; // Biến lưu giá trị vy
	CUTMAN_ACTION actionBeforeAttack; // action trước khi attack
	int actionBeforeAttackInteger;
	bool isDamaged;
	MGMDelayTime damagedDelayTime;
	MGMDelayTime timePerAction;
	MGMDelayTime blinkTime;
	FRAME_TYPE lastFrameType;
public:
	
	bool isBlink;
	bool isThrow;
	bool appearHP;
	bool appearMusic;
	int healthPoint;
	CUTMAN_ACTION action; // action hiện tại
	CUTMAN_ACTION previousAction; // action trước đó
	static CutMan* getInstance();
	void update();
	void render();
	void onLastFrameAnimation(int action);
	CUTMAN_ACTION randomAllAction();
	CUTMAN_ACTION randomActionWithoutRUN();
	void setCutmanAction(CUTMAN_ACTION curAction);
	bool randomAttack();
	void resetHeightWhenChangeAnimation();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	void onIntersectRect(MGMBox* otherObject);
	void die();
	void reset();
	CutMan();
	~CutMan();
};

