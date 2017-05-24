﻿#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"
#include "BigRock.h"
#include "SmallRock.h"

enum BOSS_GUTSMAN_ACT
{
	STAND,
	JUMP_STAND,
	JUMP,
	THROW_ROCK
};
enum JUMP_TYPE
{
	JUMP_VX,
	JUMP_NO_VX
};
enum MOVE_DIRECT
{
	TO_LEFT = -1,
	TO_RIGHT = 1
};
class BossGutsman :
	public MGMEnemy
{
	BOSS_GUTSMAN_ACT bossAction;
	MGMDelayTime delayTime;
	bool pauseAnimation;
	bool isJumping; // Đã nhảy và rơi chạm đất
	bool isThrow; // Đã ném
	bool isSetVxVy; // Đã gán vx, vy cho bigRock
	JUMP_TYPE jumpType;
	MOVE_DIRECT moveDirect;
	BigRock *bigRock;

public:
	BossGutsman();
	void update();
	void render();
	void onLastFrameAnimation(int action);
	void onCollision(MGMBox* otherObject, int nx, int ny);
	JUMP_TYPE randomJumpType();
	~BossGutsman();
};

