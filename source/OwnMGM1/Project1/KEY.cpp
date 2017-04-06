#include "KEY.h"



KEY * KEY::instance = 0;
KEY * KEY::getInstance()
{
	if (instance == 0)
		instance = new KEY();
	return instance;
}

void KEY::update()
{
	CKeyboard::getInstance()->UpdateKeyboard();
	isUpHold = CKeyboard::getInstance()->IsKeyDown(DIK_UP);
	isDownHold= CKeyboard::getInstance()->IsKeyDown(DIK_DOWN);
	isLeftDown = CKeyboard::getInstance()->IsKeyDown(DIK_LEFT) || CKeyboard::getInstance()->IsKeyDown(DIK_A);
	isRightDown = CKeyboard::getInstance()->IsKeyDown(DIK_RIGHT) || CKeyboard::getInstance()->IsKeyDown(DIK_D);
	isMoveDown = isLeftDown || isRightDown;

	isLeftPress = isLeftDown && !isPreviousLeftDown;
	isRightPress = isRightDown && !isPreviousRightDown;
	isMovePress = isLeftPress || isRightPress;

	isPreviousLeftDown = isLeftDown;
	isPreviousRightDown = isRightDown;



	isJumpDown = CKeyboard::getInstance()->IsKeyDown(DIK_SPACE);
	isJumpPress = isJumpDown && !isPreviousJumpDown;
	isPreviousJumpDown = isJumpDown;

	isAttackDown = CKeyboard::getInstance()->IsKeyDown(DIK_Z);
	isAttackPress = isAttackDown && !isPreviousAttackDown;
	isPreviousAttackDown = isAttackDown;


}

KEY::KEY()
{
	isPreviousLeftDown = false;
	isPreviousRightDown = false;
	isPreviousJumpDown = false;
	isPreviousMoveDown = false;
}
KEY::~KEY()
{
}
