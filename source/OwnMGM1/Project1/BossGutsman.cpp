#include "BossGutsman.h"
#include "Megaman.h"
#include <stdlib.h>
#include <time.h>
#include "MGMSpriteManager.h"
#include "MGMCamera.h"
#include "Room.h"
#include"Megaman.h"
#include"MegamanBullet.h"
#include"DieEffect.h"
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
	categoryEnemy = BOSS_GUTMAN;
	count = 0;
	healthPoint = 28;
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
		bigRock->objectDirection = objectDirection;
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
			sr->objectDirection = objectDirection;
			sr->init(bigRock->x, bigRock->y - 30, 16, 16);
			sr->dx = 2.4 * bigRock->objectDirection;

			// type 2
			sr = new SmallRock();
			sr->objectDirection = objectDirection;
			sr->init(bigRock->x + 16, bigRock->y - 40, 16, 16);
			sr->init(bigRock->x + 16, bigRock->y, 16, 16);
			sr->dx = 2.6 * bigRock->objectDirection;
			sr->dy = 0.6;

			// type 3
			sr = new SmallRock();
			sr->objectDirection = objectDirection;
			sr->init(bigRock->x, bigRock->y - 24, 16, 16);
			sr->dx = 2.7 * bigRock->objectDirection;
			sr->dy = 0.9;

			// type 4
			sr = new SmallRock();
			sr->objectDirection = objectDirection;
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
	if (x <= 3598)
		moveDirect = TO_RIGHT;
	MGMMovableObject::onCollision(otherObject, nx, ny); // PreventMove và Set lại vy như mọi đối tượng khác
}
void BossGutsman::onIntersectRect(MGMBox* otherObject){
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET){
		healthPoint -= 2;
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		if (healthPoint == 0){
			mgmbullet->x = this->x + this->width / 2;
			mgmbullet->y = this->y - this->height / 2;
			mgmbullet->setAction(FIRE);
			isKill = true;
			count = 0;
			Megaman::getInstance()->score += 9000;

			DieAffect* effect1 = new DieAffect(GUTMAN_DIE);
			effect1->x = this->x;
			effect1->y = this->y;
			effect1->dx = 1;
			effect1->dy = 0;

			DieAffect* effect2 = new DieAffect(GUTMAN_DIE);
			effect2->x = this->x;
			effect2->y = this->y;
			effect2->dx = 0.7;
			effect2->dy = 0;

			DieAffect* effect3 = new DieAffect(GUTMAN_DIE);
			effect3->x = this->x;
			effect3->y = this->y;
			effect3->dx = -1;
			effect3->dy = 0;

			DieAffect* effect4 = new DieAffect(GUTMAN_DIE);
			effect4->x = this->x;
			effect4->y = this->y;
			effect4->dx = -0.7;
			effect4->dy = 0;

			DieAffect* effect5 = new DieAffect(GUTMAN_DIE);
			effect5->x = this->x;
			effect5->y = this->y;
			effect5->dx = 0;
			effect5->dy = 1;

			DieAffect* effect6 = new DieAffect(GUTMAN_DIE);
			effect6->x = this->x;
			effect6->y = this->y;
			effect6->dx = 0;
			effect6->dy = 0.7;

			DieAffect* effect7 = new DieAffect(GUTMAN_DIE);
			effect7->x = this->x;
			effect7->y = this->y;
			effect7->dx = 0;
			effect7->dy = -1;

			DieAffect* effect8 = new DieAffect(GUTMAN_DIE);
			effect8->x = this->x;
			effect8->y = this->y;
			effect8->dx = 0;
			effect8->dy = -0.7;

			DieAffect* effect9 = new DieAffect(GUTMAN_DIE);
			effect9->x = this->x;
			effect9->y = this->y;
			effect9->dx = 1;
			effect9->dy = 1;

			DieAffect* effect10 = new DieAffect(GUTMAN_DIE);
			effect10->x = this->x;
			effect10->y = this->y;
			effect10->dx = 1;
			effect10->dy = -1;

			DieAffect* effect11 = new DieAffect(GUTMAN_DIE);
			effect11->x = this->x;
			effect11->y = this->y;
			effect11->dx = -1;
			effect11->dy = -1;

			DieAffect* effect12 = new DieAffect(GUTMAN_DIE);
			effect12->x = this->x;
			effect12->y = this->y;
			effect12->dx = -1;
			effect12->dy = 1;
		}
		else{
			mgmbullet->setAction(NONE);
		}
	}
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
