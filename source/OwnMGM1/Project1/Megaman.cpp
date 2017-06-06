#include"MGMCamera.h"
#include "Megaman.h"
#include"MGMSpriteManager.h"
#include"KEY.h"
#include<string>
#include"MegamanBullet.h"
#include"MGMEnemy.h"
#include "MGMItem.h"
#include <stdlib.h>
#include <time.h>
#include "EnemyBullet.h"
#include "BoardBar.h"
#include "DieEffect.h"
#include"GameOverMenu.h"
#include"Room.h"
#include"MGMAudioManager.h"
Megaman * Megaman::instance = 0;

Megaman * Megaman::getInstance()
{
	if (instance == 0)
		instance = new Megaman();
	return instance;
}
/*Cập nhật vận tốc */
void Megaman::update()
{
	bool isKeyLeftDown, isKeyRightDown, isKeyMoveDown, isKeyJumpPress, isKeyMovePress, isAttackPress;
	isKeyLeftDown = isKeyRightDown = isKeyMoveDown = isKeyJumpPress = isKeyMovePress = isAttackPress = false;
	//Nhận các sự kiện từ bàn phím
	isKeyLeftDown = KEY::getInstance()->isLeftDown;
	isKeyRightDown = KEY::getInstance()->isRightDown;
	isKeyMoveDown = KEY::getInstance()->isMoveDown;
	isKeyJumpPress = KEY::getInstance()->isJumpPress;
	isKeyMovePress = KEY::getInstance()->isMovePress;
	isAttackPress = KEY::getInstance()->isAttackPress;
	if (Room::getInstance()->isVibrate && isOnGround){
		vx = 0;
		setCurAction(MGM_EFFECT_BE_ATTACKED4);
		pauseAnimation = false;
		delayShoot.update();
		deltaUpdate();
		updateFrameAnimation();
		isOnGround = false;
		return;
	}
	if (beingAttacked){
		if (collisionDirection == LEFT){
			objectDirection = RIGHT;
		}
		if (collisionDirection == RIGHT){
			objectDirection = LEFT;
		}
		switch (actionBeingAttacked)
		{
		case STEP1:
			if (step1.isReady()){
				step1.start(200);
			}
			if (step1.isSchedule()){
				setCurAction(MGM_EFFECT_BE_ATTACKED1);
				vx = 0.2 * collisionDirection;
			}
			if (step1.isFinish()){
				actionBeingAttacked = STEP2;
			}
			step1.update();
			break;
		case STEP2:
			if (step2.isReady()){
				step2.start(100);
			}
			if (step2.isSchedule()){
				setCurAction(MGM_EFFECT_BE_ATTACKED2);
			}
			if (step2.isFinish()){
				actionBeingAttacked = STEP3;
			}
			step2.update();
			break;
		case STEP3:
			if (step3.isReady()){
				step3.start(150);
			}
			if (step3.isSchedule()){
				setCurAction(MGM_EFFECT_BE_ATTACKED3);
			}
			if (step3.isFinish()){
				actionBeingAttacked = STEP4;
				beingAttacked = false;
			}
			step3.update();
			break;
		default:
			break;
		}
	}
	else{
		if (actionBeingAttacked == STEP4){
			if (step4.isReady()){
				step4.start(3000);
			}
			if (step4.isSchedule()){
				status = MEGAMAN_BE_ATTACKED;
			}
			if (step4.isFinish()){
				beingAttacked = false;
				actionBeingAttacked = ATTACKED_NONE;
				status = MEGAMAN_NORMAL;
			}
			step4.update();
		}
		if (isKeyLeftDown)
		{
			objectDirection = LEFT;
		}
		if (isKeyRightDown)
		{
			objectDirection = RIGHT;
		}

		//Xử lý tình huống trên cầu thang
		if (isOnStairs)
		{
			isKeyMoveDown = false;
			//đang đứng trên cầu thang nhấn space sẽ rơi tự do xuống
			if (isKeyJumpPress) {
				isOnStairs = false;
				pauseAnimation = false;
				vx = 0;
			}
			if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
				MegamanBullet* bullet = new MegamanBullet();
				bullet->dx = 4 * objectDirection;
				if (objectDirection == RIGHT){
					bullet->x = x + 17;
				}
				else{
					bullet->x = x - 7;
				}
				bullet->y = y - 8;
				delayShoot.start();
				setCurAction(MGM_STAND_STAIR_ATTACK);
				lastStatusStandStairAttack = true;
				pauseAnimation = false;
				MGMAudioManager::getInstance()->Play(AUDIO_MEGA_BUSTER);
			}
			if (lastStatusStandStairAttack){
				if (delayAnimateStandStairShoot.isReady())
				{
					delayAnimateStandStairShoot.start();
				}
				if (delayAnimateStandStairShoot.isSchedule()){
					pauseAnimation = false;
					setCurAction(MGM_STAND_STAIR_ATTACK);
				}
				if (delayAnimateStandStairShoot.isFinish()){
					setCurAction(MGM_CLIMB);
					lastStatusStandStairAttack = false;
				}
				delayAnimateStandStairShoot.update();
			}
			//pauseAnimation = false;
		}
		else if (isOnGreenBar){

			isOnGreenBar = true;
			lastOnGreenBar = true;
			isOnGround = false;
			if (lastIsJump){
				lastIsJump = false;
				MGMAudioManager::getInstance()->Play(AUDIO_MEGAMAN_LAND);
			}
			if (isKeyJumpPress){
				vy = MEGAMAN_VY_JUMP;
				vx = 0;
				isOnGreenBar = false;
				lastIsJump = true;
			}

			if (isKeyMoveDown){
				if (lastStatusRunAttack){
					if (delayAnimateRunShoot.isReady())
					{
						delayAnimateRunShoot.start();
					}

					if (delayAnimateRunShoot.isFinish()){
						setCurAction(MGM_RUN);
						lastStatusRunAttack = false;
					}
					delayAnimateRunShoot.update();
				}
				else{
					setCurAction(MGM_PRE_RUN);
				}

				if (objectDirection == RIGHT && dxGreenBar > 0){
					dx = objectDirection*abs(dxGreenBar + 1.5);
				}
				if (objectDirection == RIGHT && dxGreenBar < 0){
					dx = objectDirection*abs(dxGreenBar);
				}
				if (objectDirection == LEFT && dxGreenBar < 0){
					dx = objectDirection*abs(dxGreenBar - 1.5);
				}
				if (objectDirection == LEFT && dxGreenBar > 0){
					dx = objectDirection*abs(dxGreenBar);
				}
				lastStatusStandAttack = false;

				if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
					MegamanBullet* bullet = new MegamanBullet();
					bullet->dx = 4 * objectDirection;
					if (objectDirection == 1){
						bullet->x = x + 19;
					}
					else{
						bullet->x = x - 7;
					}

					bullet->y = y - 7;
					delayShoot.start();
					setCurAction(MGM_RUN_ATTACK);
					lastStatusRunAttack = true;
					MGMAudioManager::getInstance()->Play(AUDIO_MEGA_BUSTER);
				}

			}
			else{

				dx = dxGreenBar;
				if (lastStatusStandAttack){
					if (delayAnimateStandShoot.isReady()){
						delayAnimateStandShoot.start();
					}
					if (delayAnimateStandShoot.isFinish()){
						setCurAction(MGM_STAND);
						lastStatusStandAttack = false;
					}
					if (delayAnimateStandShoot.isSchedule()){
						setCurAction(MGM_STAND_ATTACK);
					}
					delayAnimateStandShoot.update();
				}
				else{
					setCurAction(MGM_STAND);
				}
				if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3 && !Room::getInstance()->isVibrate)
				{
					MegamanBullet* bullet = new MegamanBullet();
					bullet->dx = 4 * objectDirection;
					if (objectDirection == 1){
						bullet->x = x + 19;
					}
					else{
						bullet->x = x - 7;
					}

					bullet->y = y - 8;
					delayShoot.start();
					setCurAction(MGM_STAND_ATTACK);
					lastStatusStandAttack = true;
					MGMAudioManager::getInstance()->Play(AUDIO_MEGA_BUSTER);
				}
			}
		}
		else if (isOnGround){
			if (lastIsJump){
				lastIsJump = false;
				MGMAudioManager::getInstance()->Play(AUDIO_MEGAMAN_LAND);
			}
			if (isKeyJumpPress&&!isOnGreenBar){
				vy = MEGAMAN_VY_JUMP;
				isOnGround = false;
				lastIsJump = true;
			}
			if (isKeyMoveDown){
				if (lastStatusRunAttack){
					if (delayAnimateRunShoot.isReady())
					{
						delayAnimateRunShoot.start();
					}

					if (delayAnimateRunShoot.isFinish()){
						setCurAction(MGM_RUN);
						lastStatusRunAttack = false;
					}
					delayAnimateRunShoot.update();
				}
				else{
					setCurAction(MGM_PRE_RUN);
				}
				vx = objectDirection*MEGAMAN_VX_GO;
				lastStatusStandAttack = false;

				if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
					MegamanBullet* bullet = new MegamanBullet();
					bullet->dx = 4 * objectDirection;
					if (objectDirection == 1){
						bullet->x = x + 19;
					}
					else{
						bullet->x = x - 7;
					}

					bullet->y = y - 7;
					delayShoot.start();
					setCurAction(MGM_RUN_ATTACK);
					lastStatusRunAttack = true;
					MGMAudioManager::getInstance()->Play(AUDIO_MEGA_BUSTER);
				}
			}
			else{

				vx = 0;
				if (lastStatusStandAttack){
					if (delayAnimateStandShoot.isReady()){
						delayAnimateStandShoot.start();
					}
					if (delayAnimateStandShoot.isFinish()){
						setCurAction(MGM_STAND);
						lastStatusStandAttack = false;
					}
					if (delayAnimateStandShoot.isSchedule()){
						setCurAction(MGM_STAND_ATTACK);
					}
					delayAnimateStandShoot.update();
				}
				else{
					setCurAction(MGM_STAND);
				}
				if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3 && !Room::getInstance()->isVibrate)
				{
					MegamanBullet* bullet = new MegamanBullet();
					bullet->dx = 4 * objectDirection;
					if (objectDirection == 1){
						bullet->x = x + 19;
					}
					else{
						bullet->x = x - 7;
					}

					bullet->y = y - 8;
					delayShoot.start();
					setCurAction(MGM_STAND_ATTACK);
					lastStatusStandAttack = true;
					MGMAudioManager::getInstance()->Play(AUDIO_MEGA_BUSTER);
				}

			}
		}

		if (!isOnGround && !isOnStairs && !isOnGreenBar&&!Room::getInstance()->isVibrate){
			if (lastStatusJumpAttack){
				if (delayAnimateJumpShoot.isReady())
				{
					delayAnimateJumpShoot.start();
				}
				if (delayAnimateJumpShoot.isSchedule()){
					setCurAction(MGM_JUMP_ATTACK);
				}
				if (delayAnimateJumpShoot.isFinish()){
					setCurAction(MGM_JUMP);
					lastStatusJumpAttack = false;
				}
				delayAnimateJumpShoot.update();
			}
			else{
				setCurAction(MGM_JUMP);
			}

			if (!delayShoot.isSchedule() && isAttackPress && MegamanBullet::getListBullet()->Count < 3){
				MegamanBullet* bullet = new MegamanBullet();
				bullet->dx = 4 * objectDirection;
				if (objectDirection == 1){
					bullet->x = x + 17;
				}
				else{
					bullet->x = x - 7;
				}
				bullet->y = y - 8;
				delayShoot.start();
				setCurAction(MGM_JUMP_ATTACK);
				lastStatusJumpAttack = true;
				MGMAudioManager::getInstance()->Play(AUDIO_MEGA_BUSTER);
			}
			if (isKeyMoveDown){
				if (lastOnGreenBar){
					vx = objectDirection*0.5;
					lastOnGreenBar = false;
				}
				else{
					vx = objectDirection*MEGAMAN_VX_GO;
				}
			}
		}
	}
	//pauseAnimation = false;
	delayShoot.update();
	deltaUpdate();
	updateFrameAnimation();
	isOnGround = false;
	isOnGreenBar = false;
}
void Megaman::deltaUpdate(){
	if (!isOnGreenBar){
		vx = vx + ax * GAMETIME;
		dx = vx * GAMETIME;
	}
	vy = vy + ay * GAMETIME;
	if (vy <= -0.9f)
		vy = -0.9f;
	dy = vy * GAMETIME;
}

void Megaman::render()
{
	if (sprite == 0)
		return;
	float xDraw, yDraw;
	MGMCamera::getInstance()->Transform(x, y, xDraw, yDraw);
	//Nếu hướng object khác hướng hình vẽ( hướng hình vẽ = left(-1))

	int widthSprite = sprite->animations[curAction].frames[curFrame].width;
	/*if (curAction != MGM_CLIMB)*/
	xDraw -= (widthSprite - width) / 2;

	if (objectDirection != sprite->pImage->imageDirection)
	{
		//Lật x bằng cách nhân tất cả điểm ảnh cho ma trận bên dưới
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			2 * (xDraw + widthSprite / 2), 0, 0, 1)));
	}
	this->sprite->Render(xDraw, yDraw, curAction, curFrame);
	if (objectDirection != sprite->pImage->imageDirection)
	{
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)));
	}
}

void Megaman::setCurAction(int action)
{
	if (this->action == MGM_RUN && action == MGM_PRE_RUN)
		return;
	this->action = action;
	MGMMovableObject::setCurAction(action);
}

void Megaman::onIntersectRect(MGMBox * otherObject)
{
	
	if (otherObject->collisionCategory == CC_ITEM){
		MGMItem* item = (MGMItem*)otherObject;
		if (item->categoryItem == CI_LIFE_ENERGY_BIG){
			int result = rand() % 3 + 8;
			healthPoint += result;
		}
		if (item->categoryItem == CI_LIFE_ENERGY_SMALL){
			int result = rand() % 3 + 2;
			healthPoint += result;
		}
		if (item->categoryItem == CI_UP){
			MGMAudioManager::getInstance()->Play(AUDIO_1UP);
			life++;
		}
		if (item->categoryItem == CI_BONUS_BALL){
			MGMAudioManager::getInstance()->Play(AUDIO_BONUS_BALL);
		}
	}
	if (healthPoint > 28){
		healthPoint = 28;
	}
	if (otherObject->collisionCategory == CC_ENEMY){
		MGMEnemy* enemy = (MGMEnemy*)otherObject;
		if (actionBeingAttacked == ATTACKED_NONE){
			if (enemy->categoryEnemy != ROOM && enemy->categoryEnemy != GREEN_BAR){
				beingAttacked = true;
				MGMAudioManager::getInstance()->Play(AUDIO_MEGAMAN_DAMAGE);
				actionBeingAttacked = STEP1;
				collisionDirection = enemy->objectDirection;
			}

			if ((enemy->categoryEnemy == CREP_BEAK) || (enemy->categoryEnemy == CREP_FLYING_SHELL) || (enemy->categoryEnemy == CREP_SCREW_BOMBER) || (enemy->categoryEnemy == CREP_MET)){
				healthPoint -= 1;
			}
			if (enemy->categoryEnemy == CREP_FLEA){
				healthPoint -= 2;
			}
			if (enemy->categoryEnemy == CREP_BLADER){
				healthPoint -= 3;
			}
			if ((enemy->categoryEnemy == CREP_OCTOPUS_BATTERY) || (enemy->categoryEnemy == CREP_SUPER_CUTTER) || (enemy->categoryEnemy == BOSS_GUTMAN) || (enemy->categoryEnemy == BIG_ROCK) || (enemy->categoryEnemy == SMALL_ROCK)){
				healthPoint -= 4;
			}
			if (enemy->categoryEnemy == CREP_BIG_EYE){
				healthPoint -= 10;
			}
			if (enemy->categoryEnemy == DEATH_LAND){
				healthPoint -= 28;
			}
		}
	}
	if (otherObject->collisionCategory == CC_ENEMY_BULLET){
		EnemyBullet* bullet = (EnemyBullet*)otherObject;
		if (actionBeingAttacked == ATTACKED_NONE){
			MGMAudioManager::getInstance()->Play(AUDIO_MEGAMAN_DAMAGE);
			beingAttacked = true;
			actionBeingAttacked = STEP1;
			collisionDirection = bullet->objectDirection;
			if (bullet->categoryBullet == FOR_BEAK){
				healthPoint -= 1;
			}
			if ((bullet->categoryBullet == FOR_FLYING_SHELL) || (bullet->categoryBullet == FOR_SCREW_BOMBER) || (bullet->categoryBullet == FOR_MET)){
				healthPoint -= 2;
			}
			if (bullet->categoryBullet == FOR_PKM){
				healthPoint -= 3;
			}
		}
	}
	if (healthPoint <= 0){
		die();
		healthPoint = 0;
	}
}

void Megaman::onLastFrameAnimation(int action)
{
	bool isKeyMoveDown = KEY::getInstance()->isMoveDown;
	if (action == MGM_PRE_RUN && isKeyMoveDown)
	{
		setCurAction(MGM_RUN);
	}
}

void Megaman::updateFrameAnimation()
{
	if (!pauseAnimation){
		if (status == MEGAMAN_NORMAL){
			if (curAction == MGM_STAND){
				if (eyesTime1.isReady() && eyesTime2.isFinish()){
					eyesTime1.start(1500);
				}
				if (eyesTime2.isReady() && eyesTime1.isFinish()){
					eyesTime2.start(100);
				}
				if (eyesTime1.isSchedule()){
					curFrame = 0;
				}
				if (eyesTime2.isSchedule()){
					curFrame = 1;
				}
				eyesTime1.update();
				eyesTime2.update();
			}
			else{
				if (timeFrame.atTime()) {
					int lastFrame = curFrame;
					this->sprite->Update(curAction, curFrame);
					if (curAction == MGM_RUN && curFrame == 3)
						curFrame = 0;
					else if (curAction == MGM_JUMP && curFrame == 1)
						curFrame = 0;
					else if (curAction == MGM_JUMP_ATTACK && curFrame == 1)
						curFrame = 0;
					else if (curAction == MGM_STAND_ATTACK && curFrame == 1)
						curFrame = 0;
					else if (curAction == MGM_CLIMB && curFrame == 2)
						curFrame = 0;
					else if (curAction == MGM_RUN_ATTACK && curFrame == 3)
						curFrame = 0;
					else if (curAction == MGM_STAND_STAIR_ATTACK&& curFrame == 1)
						curFrame = 0;
					else if (curAction == MGM_EFFECT_BE_ATTACKED4&&curFrame == 1)
						curFrame = 0;

					if (lastFrame == this->sprite->animations[curAction].framesCount - 1 && curFrame == 0)
						onLastFrameAnimation(curAction);
				}
			}
		}
		else if (status == MEGAMAN_BE_ATTACKED){
			if (timeFrame1.atTime()){
				int lastFrame = curFrame;
				this->sprite->Update(curAction, curFrame);
				if (curAction == MGM_STAND &&  curFrame == 1){
					curFrame = 2;
				}
				if (lastFrame == this->sprite->animations[curAction].framesCount - 1 && curFrame == 0)
					onLastFrameAnimation(curAction);
			}
		}
	}
}

void Megaman::onCollision(MGMBox * otherObject, int nx, int ny)
{
	MGMMovableObject::onCollision(otherObject, nx, ny);
	if (ny == 1)
	{
		isOnGround = true;
		isOnStairs = false;
	}
	if (otherObject->collisionCategory == CC_ENEMY){
		MGMEnemy *m = (MGMEnemy*)otherObject;
		if (m->categoryEnemy == GREEN_BAR && ny == 1){
			if (m->curFrame == 0){

				isOnGreenBar = true;
				Collision::preventMove(this, otherObject, nx, ny);
			}
			else{
				isOnGreenBar = false;
			}
			isOnGround = false;
			dxGreenBar = otherObject->dx;
		}
	}
	else{

		isOnGreenBar = false;
	}
}
void Megaman::die(){
	if (!isKill){
		MGMAudioManager::getInstance()->Play(AUDIO_MEGAMAN_DEFEATE);
		
		DieAffect* effect1 = new DieAffect(MEGAMAN_DIE);
		effect1->x = this->x;
		effect1->y = this->y;
		effect1->dx = 1;
		effect1->dy = 0;

		DieAffect* effect2 = new DieAffect(MEGAMAN_DIE);
		effect2->x = this->x;
		effect2->y = this->y;
		effect2->dx = 0.7;
		effect2->dy = 0;

		DieAffect* effect3 = new DieAffect(MEGAMAN_DIE);
		effect3->x = this->x;
		effect3->y = this->y;
		effect3->dx = -1;
		effect3->dy = 0;

		DieAffect* effect4 = new DieAffect(MEGAMAN_DIE);
		effect4->x = this->x;
		effect4->y = this->y;
		effect4->dx = -0.7;
		effect4->dy = 0;

		DieAffect* effect5 = new DieAffect(MEGAMAN_DIE);
		effect5->x = this->x;
		effect5->y = this->y;
		effect5->dx = 0;
		effect5->dy = 1;

		DieAffect* effect6 = new DieAffect(MEGAMAN_DIE);
		effect6->x = this->x;
		effect6->y = this->y;
		effect6->dx = 0;
		effect6->dy = 0.7;

		DieAffect* effect7 = new DieAffect(MEGAMAN_DIE);
		effect7->x = this->x;
		effect7->y = this->y;
		effect7->dx = 0;
		effect7->dy = -1;

		DieAffect* effect8 = new DieAffect(MEGAMAN_DIE);
		effect8->x = this->x;
		effect8->y = this->y;
		effect8->dx = 0;
		effect8->dy = -0.7;

		DieAffect* effect9 = new DieAffect(MEGAMAN_DIE);
		effect9->x = this->x;
		effect9->y = this->y;
		effect9->dx = 1;
		effect9->dy = 1;

		DieAffect* effect10 = new DieAffect(MEGAMAN_DIE);
		effect10->x = this->x;
		effect10->y = this->y;
		effect10->dx = 1;
		effect10->dy = -1;

		DieAffect* effect11 = new DieAffect(MEGAMAN_DIE);
		effect11->x = this->x;
		effect11->y = this->y;
		effect11->dx = -1;
		effect11->dy = -1;

		DieAffect* effect12 = new DieAffect(MEGAMAN_DIE);
		effect12->x = this->x;
		effect12->y = this->y;
		effect12->dx = -1;
		effect12->dy = 1;
		isKill = true;
		dx = 0;
		dy = 0;
		actionBeingAttacked == ATTACKED_NONE;
		GameOverMenu::getInstance()->isStart = true;
	}
}

Megaman::Megaman()
{
	lastIsJump = true;
	lastOnGreenBar = false;
	actionBeingAttacked = ATTACKED_NONE;
	status = MEGAMAN_NORMAL;
	sprite = MGMSpriteManager::getInstance()->sprites[SPR_MEGAMAN];
	beingAttacked = false;
	score = 0;
	life = 2;
	healthPoint = 28;
	width = 16;
	height = 23;
	ax = 0;
	vx = 0;
	delayShoot.init(150);
	isOnGreenBar = false;
	isOnGround = false;
	isOnStairs = false;
	pauseAnimation = false;
	collisionCategory = CC_MEGAMAN;
	IntersectDoor = -1;
	eyesTime1.init(100);
	eyesTime2.init(100);
	timeFrame2.tickPerFrame = 500;
	timeFrame1.tickPerFrame = 50;
	timeFrame.tickPerFrame = 80;
	delayAnimateStandShoot.init(250);
	delayAnimateRunShoot.init(300);
	delayAnimateJumpShoot.init(200);
	delayAnimateStandStairShoot.init(200);
}

Megaman::~Megaman()
{
}
