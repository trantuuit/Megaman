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
	isLeftDown = CKeyboard::getInstance()->IsKeyDown(DIK_LEFT)|| CKeyboard::getInstance()->IsKeyDown(DIK_A);
	isRightDown = CKeyboard::getInstance()->IsKeyDown(DIK_RIGHT) || CKeyboard::getInstance()->IsKeyDown(DIK_D);

	isJumpDown = CKeyboard::getInstance()->IsKeyDown(DIK_SPACE);
	isJumpPress = isJumpDown && !isPreviousJumpDown;
	isPreviousJumpDown = isJumpDown;

	isMoveDown = isLeftDown || isRightDown;

}

KEY::KEY()
{
	isPreviousJumpDown = false;
}


KEY::~KEY()
{
}
