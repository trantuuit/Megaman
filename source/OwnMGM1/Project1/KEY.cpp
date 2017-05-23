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
	isUpHold = CKeyboard::getInstance()->IsKeyDown(DIK_UP) || CKeyboard::getInstance()->IsKeyDown(DIK_W);
	isDownHold = CKeyboard::getInstance()->IsKeyDown(DIK_DOWN) || CKeyboard::getInstance()->IsKeyDown(DIK_S);
	isLeftDown = CKeyboard::getInstance()->IsKeyDown(DIK_LEFT) || CKeyboard::getInstance()->IsKeyDown(DIK_A);
	isRightDown = CKeyboard::getInstance()->IsKeyDown(DIK_RIGHT) || CKeyboard::getInstance()->IsKeyDown(DIK_D);
	isEnterDown = CKeyboard::getInstance()->IsKeyDown(DIK_RETURN) || CKeyboard::getInstance()->IsKeyDown(DIK_NUMPADENTER);
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

	isPauseBoardDown = CKeyboard::getInstance()->IsKeyDown(DIK_P);
	isResumeBoardDown = CKeyboard::getInstance()->IsKeyDown(DIK_O);
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
