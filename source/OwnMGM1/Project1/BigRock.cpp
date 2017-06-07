#include "BigRock.h"


BigRock::BigRock()
{
	vx = 0;
	vy = 0;
	ax = 0;
	ay = 0;
	dx = 0;
	dy = 0;
	collisionCategory = CC_BIGROCK;
	isMoving = false;
	isDelay = false;
	isBreak = false;
	isVibrate = false;
	categoryEnemy = BIG_ROCK;
}

void BigRock::update()
{
	MGMMovableObject::update();
}


void BigRock::render()
{

	if (isVibrate == true && isMoving == false) // Trạng thái rung = true áp dụng với viên gạch không thể ném
		if (vibrateCount <= 35) //Chỉ rung một số lần hữu hạn
		{
			MGMObject::vibrateRender();
			vibrateCount++;
		}
		else // Đã rung đủ số lần
		{
			isVibrate = false;
			vibrateCount = 0;
			MGMEnemy::render();
		}
	else
		MGMEnemy::render();
}

void BigRock::onIntersectRect(MGMBox * otherObject)
{
	if (otherObject->collisionCategory == CC_MEGAMAN)
	{
		if (isMoving == true) // Viên gạch này có thể ném được
		{
			isBreak = true;
		}
	}
}

void BigRock::onCollision(MGMBox * otherObject, int nx, int ny)
{
	// Bị chặn bởi Gutsman:
	if (otherObject->collisionCategory == CC_ENEMY)
	{

		if (isMoving == true) // Viên gạch này có thể ném được
		{
			Collision::preventMove(this, otherObject, nx, ny);
			// Khi rớt xuống chạm tay Gutsman thì cho vy, ay = 0
			vy = 0;
			ay = 0;
		}
	}
	else // Chạm các object khác thì biến mất:
	{
		if (isMoving == true) // Viên gạch này có thể ném được
		{
			isBreak = true;
		}
	}
}

BigRock::~BigRock()
{
}
