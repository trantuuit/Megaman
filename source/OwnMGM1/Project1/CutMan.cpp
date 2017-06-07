#include "CutMan.h"
#include "CutmanBullet.h"
#include "Megaman.h"
#include "Door.h"
#include <stdlib.h>
#include <time.h>
#include "MegamanBullet.h"
#include "Blink.h"

CutMan* CutMan::cutman = 0;
CutMan* CutMan::getInstance()
{
	if (cutman == 0)
	{
		cutman = new CutMan();
	}
	return cutman;
}
CutMan::CutMan()
{
	action = CM_CLAP;
	curFrame = 0;
	vy = -0.2f;
	vx = 0;
	ay = GRAVITY;
	objectDirection = LEFT;
	timeFrame = 200;
	timePerAction.init(1000);
	isSaveVy = false;
	isJumping = false;
	isThrow = false;
	isBlink = false;
	pauseAnimation = false;
	lastFrameType = HEIGHT_32;
	damagedDelayTime.init(700);
	blinkTime.init(1200);
}

void CutMan::update()
{
	if (!pauseAnimation)
		MGMMovableObject::updateFrameAnimation();


	int distance = Megaman::getInstance()->getXCenter() - this->getXCenter();
	objectDirection = (distance < 0) ? LEFT : RIGHT;
	if (damagedDelayTime.isFinish()) // Nếu hết thời gian delay do bị trúng đạn:
	{
		if (action == CM_IS_DAMAGED)
		{
			vx = 0;
			action = randomAllAction();
			setCutmanAction(action);
		}

		switch (action)
		{
		case CM_RUN:
			if (distance <= 2 && distance >= -2) // Nếu đứng sát Megaman thì không RUN mà chuyển sang JUMP
			{
				action = randomActionWithoutRUN();
				setCutmanAction(action);
				//break;
			}
			else
			{
				(isThrow) ? setCurAction(7) : setCurAction(2);
				vx = (distance == 0) ? 0 : 0.17 * objectDirection;
				//vy = -0.2;
				if (timePerAction.isFinish()) // Chuyển qua action khác
				{
					previousAction = CM_RUN;
					timePerAction.start();
					action = randomAllAction();
				}
				break;
			}

		case CM_JUMP:
			if (/*timePerAction.isFinish() &&*/ isJumping == false)
			{
				previousAction = CM_JUMP;
				vx = 0.2 * objectDirection;
				vy = (isSaveVy == true) ? vyBeforeAttack : 1.2;
				isSaveVy = false;
				isJumping = true;
				(isThrow) ? setCurAction(6) : setCurAction(1);

				//action = CM_CLAP; // Việc chuyển action sẽ thực hiện ở onCollision khi nhảy chạm đất
			}
			break;
		case CM_CLAP:
			setCutmanAction(action);
			vx = 0;
			vy = 0;
			if (timePerAction.isFinish()) // Chuyển action
			{
				previousAction = CM_CLAP;
				action = randomAllAction();
				timePerAction.start(500);
			}
			break;
		case CM_ATTACK:
			if (timePerAction.isFinish()) // Hết thời gian delay
			{
				action = actionBeforeAttack; // Trả lại action trước khi attack
				setCutmanAction(action);
				pauseAnimation = false;
			}
			break;
		default:
			break;
		}
		//------------------------------------------
		//Điều kiện để ATTACK bao gồm chưa ném bullet và action != ATTACK
		if (randomAttack() && !isThrow && action != CM_ATTACK)
		{

			if (action != CM_ATTACK) // Tránh việc action == CM_ATTACK liên tục
			{
				actionBeforeAttack = previousAction; //Lưu action hiện tại trước khi thực hiện acttack
			}
			if (previousAction != CM_JUMP)
			{
				vx = 0; // Khi attack thì vx = 0 (trừ khi vừa nhảy vừa attack)
			}

			if (previousAction == CM_JUMP) // Nếu trước khi attack là đang JUMP
			{
				vyBeforeAttack = vy; // Lưu vy để gán lại sau khi attack
				isSaveVy = true;
			}
			action = CM_ATTACK; //chuyển sang ATTACK
			setCurAction(3);
			timePerAction.start(500);
		}

		if (action == CM_ATTACK && curFrame == 1)
		{
			isThrow = true;
		}
		// Bị trúng đạn
		if (isDamaged)
		{
			vx = 0.17 * (-objectDirection); // Cho vx = 0
			vy = 0;
			action = CM_IS_DAMAGED; //Chuyển qua Animation trúng đạn
									//(isThrow) ? setCurAction(8) : setCurAction(4); // Chuyển Animation
									//action = randomAction(); // Random hành động khác
			setCutmanAction(action);
			if (!damagedDelayTime.isSchedule()) // Nếu chưa delay thì delay
				damagedDelayTime.start(); // Delay

										  // Tạo hình nhấp nháy
			isBlink = true;
			blinkTime.start();

		}
	}
	if (!isThrow && action == CM_IS_DAMAGED) //Nếu đang trúng đạn mà bullet quay về:
		setCurAction(4);

	isDamaged = false; //Trả lại giá trị false sau khi đã trúng đạn

	if (isBlink && !blinkTime.isFinish()) //Cập nhật tọa độ Blink
	{
		Blink::getInstance()->x = x;
		Blink::getInstance()->y = getBottom() + 24;
	}

	blinkTime.update();
	damagedDelayTime.update();
	timePerAction.update();
	MGMMovableObject::deltaUpdate();
}
void CutMan::render()
{
	resetHeightWhenChangeAnimation();
	if (isBlink && !blinkTime.isFinish()) // Nếu còn trong khoảng thời gian nhấp nháy
	{
		Blink::getInstance()->render();
		if (!Blink::getInstance()->isRender)
			MGMEnemy::render();
	}
	else
	{
		isBlink = false;
		MGMEnemy::render();
	}
}
void CutMan::onLastFrameAnimation(int _action)
{
	switch (_action)
	{
	case 3: // curAction == 3 là ATTACK
		curFrame = 1;
		pauseAnimation = true;
		break;
	default:
		break;
	}
}
CUTMAN_ACTION CutMan::randomAllAction()
{
	srand(time(NULL));
	int result = rand() % 100;
	if (result >= 0 && result <= 50)
		return CM_RUN;
	if (result > 50 && result <= 90)
		return CM_JUMP;
	else
		return CM_CLAP;
}
CUTMAN_ACTION CutMan::randomActionWithoutRUN()
{
	srand(time(NULL));
	int result = rand() % 100;
	if (result >= 0 && result <= 60)
		return CM_JUMP;
	else
		return CM_CLAP;
}
bool CutMan::randomAttack()
{
	srand(time(NULL));
	int result = rand() % 3;
	return (result != 0) ? false : true;
}

void CutMan::onIntersectRect(MGMBox * otherObject)
{
	// Set action cho viên đạn khi chạm BossCutman
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET && !isBlink)
	{
		if (!isDamaged)
			isDamaged = true;
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		mgmbullet->setAction(NONE);
	}
}

void CutMan::onCollision(MGMBox* otherObject, int nx, int ny)
{
	if (ny != 0 && (otherObject->collisionCategory == CC_GROUND || otherObject->collisionCategory == CC_BIGROCK))
	{
		vy = -0.25;
		if (previousAction == CM_JUMP) //Nếu nhảy chạm đất
		{
			vx = 0;
			isSaveVy = false; //Không lưu giá trị vy lúc còn nhảy
			if (/*timePerAction.isFinish() &&*/ damagedDelayTime.isFinish())
			{
				pauseAnimation = false;
				action = randomAllAction();
				setCutmanAction(action);
			}
		}

	}
	if (otherObject->collisionCategory == CC_GROUND || otherObject->collisionCategory == CC_BIGROCK)
	{
		// Chặn va chạm khi nhảy chạm nền
		if (ny == 1)
			isJumping = false;
		Collision::preventMove(this, otherObject, nx, ny);
	}


	// Set action cho viên đạn khi chạm BossCutman
	if (otherObject->collisionCategory == CC_MEGAMAN_BULLET && !isBlink)
	{
		if (!isDamaged)
		{
			isDamaged = true;
		}
		MegamanBullet* mgmbullet = (MegamanBullet*)otherObject;
		mgmbullet->setAction(NONE);
	}
}


void CutMan::resetHeightWhenChangeAnimation()
{

	switch (curAction)
	{
	case 0: case 1: case 2: case 3: case 4:
		if (curAction == 3 && curFrame == 1)
		{
			height = 24;
			if (lastFrameType == HEIGHT_32)
				y -= 8;
			lastFrameType = HEIGHT_24;
		}
		else
		{
			height = 32;
			if (lastFrameType == HEIGHT_24)
				y += 8;
			lastFrameType = HEIGHT_32;
		}

		break;

	case 5: case 6: case 7: case 8:
		height = 24;
		if (lastFrameType == HEIGHT_32)
			y -= 8;
		lastFrameType = HEIGHT_24;
		break;

	default:
		break;
	}
}

void CutMan::setCutmanAction(CUTMAN_ACTION _curAction)
{
	switch (_curAction)
	{
	case CM_RUN:
		(isThrow) ? setCurAction(7) : setCurAction(2);
		break;
	case CM_JUMP:
		(isThrow) ? setCurAction(6) : setCurAction(1);
		break;
	case CM_CLAP:
		(isThrow) ? setCurAction(5) : setCurAction(0);
		break;
	case CM_IS_DAMAGED:
		(isThrow) ? setCurAction(8) : setCurAction(4);
		break;
	default:
		break;
	}
}

CutMan::~CutMan()
{
}
