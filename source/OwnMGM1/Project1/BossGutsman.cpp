#include "BossGutsman.h"
#include "Megaman.h"
#include <stdlib.h>
#include <time.h>
#include "MGMSpriteManager.h"
#include "MGMCamera.h"
#include "Room.h"



BossGutsman::BossGutsman()
{
	vx = 0;
	ax = 0;
	timeFrame = 300;
	bossAction = STAND;
	delayTime.init(300);
	jumpType = JUMP_NO_VX;
	moveDirect = TO_LEFT;
	isThrow = false;
	isSetVxVy = false;
}

void BossGutsman::update()
{
	objectDirection = (Megaman::getInstance()->getXCenter() < this->getXCenter()) ? LEFT : RIGHT;
	switch (bossAction)
	{
	case STAND:
		if (delayTime.isFinish())
		{
			vx = 0;
			vy = 0;
			pauseAnimation = false;
		}
		break;
	case JUMP:
		// Nếu chưa nhảy thì nhảy (tránh trường hợp bay lên trời :))
		if (delayTime.isFinish() && isJumping == false)
		{
			setCurAction(1);
			vy = 0.8;
			jumpType = randomJumpType(); // Random kiểu nhảy, từ đó Set vx
			vx = (jumpType == JUMP_NO_VX) ? 0 : (0.2 * moveDirect);
			isJumping = true; //Xác nhận đã nhảy
			pauseAnimation = false;
		}
		break;
	case THROW_ROCK:
		if (delayTime.isFinish())
		{
			vx = 0;
			vy = 0;
			pauseAnimation = false;
		}
		break;
	default:
		break;
	}

	delayTime.update();
	deltaUpdate();
	if (!pauseAnimation)
		updateFrameAnimation();

	//-----------------------------------ROCK---------------------------------------------

	if (bossAction == THROW_ROCK && isThrow == false)
	{
		bigRock = new BigRock();
		bigRock->vy = -0.1;
		bigRock->ay = GRAVITY;
		bigRock->init(this->x - (10 * objectDirection), 220, 32, 32);
		bigRock->sprite = MGMSpriteManager::getInstance()->sprites[SPR_BIGROCK];
		bigRock->objectDirection = this->objectDirection;
		bigRock->isMoving = true; // Để phân biệt rằng viên gạch này có thể di chuyển được
		bigRock->height = 28; // Giảm height sao cho viên gạch chạm tay Gutsman
		isThrow = true; // Xác nhận đã ném
		bigRock->isDelay = false;

	}

	if (bigRock != NULL)
	{
		if (bossAction == THROW_ROCK && curFrame == 2 && isSetVxVy == false) // Ném:
		{
			int distanceX = Megaman::getInstance()->x - bigRock->x;
			int distanceY = Megaman::getInstance()->getTop() - bigRock->getTop();

			bigRock->vx = 0.04 * (distanceX / GAMETIME);
			bigRock->vy = 0.04 * (distanceY / GAMETIME);
			bigRock->ay = 0;
			bigRock->height = 32; // Reset height để xét va chạm cho chính xác
			isSetVxVy = true;
		}

		bigRock->update();

		//-----------------------------------Xét va chạm cho bigRock------------------------
		Collision::checkCollision(bigRock, this);
		Collision::checkCollision(bigRock, Megaman::getInstance());
		List<MGMObject*>& bigRocks = MGMCamera::getInstance()->objects.bigRockObjects;
		for (int i = 0; i < bigRocks.size(); i++)
			Collision::checkCollision(bigRock, bigRocks[i]);
		bigRock->coordinateUpdate();
		//-----------------------------------------------------------------------------------

		//------------------------------------------SMALL ROCK-------------------------------
		if (bigRock->isBreak == true)
		{
			// 1 và 4 sẽ bay theo phương ngang còn 2 và 3 sẽ bay hướng lên
			// type 1
			SmallRock *sr = new SmallRock();
			sr->init(bigRock->x, bigRock->y - 30, 16, 16);
			sr->dx = 2.4 * bigRock->objectDirection;

			// type 2
			sr = new SmallRock();
			sr->init(bigRock->x + 16, bigRock->y - 40, 16, 16);
			sr->init(bigRock->x + 16, bigRock->y, 16, 16);
			sr->dx = 2.6 * bigRock->objectDirection;
			sr->dy = 0.6;

			// type 3
			sr = new SmallRock();
			sr->init(bigRock->x, bigRock->y - 24, 16, 16);
			sr->dx = 2.7 * bigRock->objectDirection;
			sr->dy = 0.9;

			// type 4
			sr = new SmallRock();
			sr->init(bigRock->x + 16, bigRock->y - 40, 16, 16);
			sr->dx = 2.6 * bigRock->objectDirection;

		}

		// Ra khỏi Camera hoặc va chạm thì biến mất:
		if (Collision::AABBCheck(MGMCamera::getInstance(), bigRock) == false || bigRock->isBreak == true)
		{
			bigRock = NULL;
		}
	}
	if (bossAction == JUMP)
	{
		isThrow = false;
		isSetVxVy = false;
	}

}
void BossGutsman::onLastFrameAnimation(int action)
{
	// Tại frame cuối cùng của mỗi hành động:
	switch (bossAction)
	{
	case STAND: // Chuyển sang JUMP
		delayTime.start();
		bossAction = JUMP;
		isJumping = false; // Chưa thực hiện việc nhảy
		pauseAnimation = true;
		curFrame = 2;
		break;
	case JUMP:
		// Sẽ chuyển qua Action khác ở hàm onCollision
		break;
	case THROW_ROCK: // Chuyển sang JUMP
		delayTime.start();
		bossAction = JUMP;
		isJumping = false; // Chưa thực hiện việc nhảy
		pauseAnimation = true;
		curFrame = 3;
		break;
	default:
		break;
	}
}
void BossGutsman::onCollision(MGMBox * otherObject, int nx, int ny)
{
	// Khi rớt chạm nền thì set vx = 0 để không bị trượt
	if ((bossAction == STAND || bossAction == THROW_ROCK)
		&& (otherObject->collisionCategory == CC_GROUND || otherObject->collisionCategory == CC_BIGROCK)
		&& nx == 0)
	{
		vx = 0;
	}

	// Khi nhảy rớt chạm nền thì chuyển qua Action khác:
	// Điều kiện isJumping == true để xác nhận việc đã nhảy và rớt xuống, phân biệt với trường hợp mới bắt đầu nhảy
	if ((bossAction == JUMP) && isJumping == true && nx == 0)
	{
		delayTime.start(400);
		if (jumpType == JUMP_NO_VX)
		{
			bossAction = THROW_ROCK;
			setCurAction(2); //Chuyển qua frame đầu của hành động tiếp theo
		}
		else
		{
			bossAction = STAND;
			setCurAction(0); //Chuyển qua frame đầu của hành động tiếp theo
		}
		pauseAnimation = true; // Trong khi đang delay thì dừng updateFrameAnimation

		Room::isVibrate = true; // Làm đối tượng Room bị rung chuyển
								// Làm 2 viên gạch lớn bị rung chuyển:
		List<MGMObject*>& bigRocks = MGMCamera::getInstance()->objects.bigRockObjects;
		for (int i = 0; i < bigRocks.size(); i++)
		{
			BigRock *b = (BigRock*)bigRocks[i];
			b->isVibrate = true;
		}
	}

	// Khi chạm 2 bên tường thì đổi hướng di chuyển
	if (otherObject->collisionCategory == CC_GROUND && nx != 0)
	{
		moveDirect = (nx == -1) ? TO_LEFT : TO_RIGHT;
		vx = 0;
	}
	MGMMovableObject::onCollision(otherObject, nx, ny); // PreventMove và Set lại vy như mọi đối tượng khác
}

JUMP_TYPE BossGutsman::randomJumpType()
{
	srand(time(NULL));
	int result = rand() % 2;
	return (result != 1) ? JUMP_VX : JUMP_NO_VX;
}

void BossGutsman::render()
{
	MGMEnemy::render();
	if (bigRock != NULL)
		bigRock->render();
}

BossGutsman::~BossGutsman()
{
}
