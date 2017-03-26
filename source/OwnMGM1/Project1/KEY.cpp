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
	isLeftDown = CKeyboard::getInstance()->IsKeyDown(DIK_LEFT) || CKeyboard::getInstance()->IsKeyDown(DIK_A);
	isRightDown = CKeyboard::getInstance()->IsKeyDown(DIK_RIGHT) || CKeyboard::getInstance()->IsKeyDown(DIK_D);
	isMoveDown = isLeftDown || isRightDown;
	isJumpDown = CKeyboard::getInstance()->IsKeyDown(DIK_SPACE);

	isLeftPress = isLeftDown && !isPreviousLeftDown;
	isRightPress = isRightDown && !isPreviousRightDown;
	isMovePress = isLeftPress || isRightPress;
	isJumpPress = isJumpDown && !isPreviousJumpDown;



	isPreviousLeftDown = isLeftDown;
	isPreviousRightDown = isRightDown;
	isPreviousJumpDown = isJumpDown;


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
