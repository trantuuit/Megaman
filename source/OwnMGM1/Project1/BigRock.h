#pragma once
#include "MGMEnemy.h"
#include "MGMDelayTime.h"
class BigRock :
	public MGMEnemy
{
public:
	MGMDelayTime delayBeforeThrow;
	bool isMoving; // Phân biệt viên gạch này do Gutsman ném
	bool isDelay; // Đã delay trước khi ném đi
	bool isBreak; // Dã vỡ


	bool isVibrate; // Biến thiết lập rung hoặc không
	int vibrateCount; // Số frame trong 1 lần rung

	BigRock();
	void update();
	void render();
	void onCollision(MGMBox* otherObject, int nx, int ny);
	~BigRock();
};

