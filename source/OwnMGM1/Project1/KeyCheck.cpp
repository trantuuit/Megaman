#include "KeyCheck.h"



KeyCheck * KeyCheck::instance = 0;
KeyCheck * KeyCheck::getInstance()
{
	if (instance == 0)
		instance = new KeyCheck();
	return instance;
}

void KeyCheck::update()
{
	CKeyboard::getInstance()->UpdateKeyboard();


	isUpHold = CKeyboard::getInstance()->IsKeyDown(DIK_UP) || CKeyboard::getInstance()->IsKeyDown(DIK_W);
	isDownHold = CKeyboard::getInstance()->IsKeyDown(DIK_DOWN) || CKeyboard::getInstance()->IsKeyDown(DIK_S);
	isLeftDown = CKeyboard::getInstance()->IsKeyDown(DIK_LEFT) || CKeyboard::getInstance()->IsKeyDown(DIK_A);
	isRightDown = CKeyboard::getInstance()->IsKeyDown(DIK_RIGHT) || CKeyboard::getInstance()->IsKeyDown(DIK_D);
	
	
	isMoveDown = isLeftDown || isRightDown;

	isLeftPress = isLeftDown && !isPreviousLeftDown;
	isRightPress = isRightDown && !isPreviousRightDown;
	isMovePress = isLeftPress || isRightPress;

	isPreviousLeftDown = isLeftDown;
	isPreviousRightDown = isRightDown;

	isEnterDown = CKeyboard::getInstance()->IsKeyDown(DIK_RETURN) || CKeyboard::getInstance()->IsKeyDown(DIK_NUMPADENTER);
	isEnterPress = isEnterDown && !isPreviousEnter;
	isPreviousEnter = isEnterDown;

	/*isOneDown = CKeyboard::getInstance()->IsKeyDown(DIK_1);
	isOnePress = isOneDown && !isPreviousOne;
	isPreviousOne = isOneDown;*/
	
	//isOnePress = CKeyboard::getInstance()->IsKeyPress(DIK_1);



	isJumpDown = CKeyboard::getInstance()->IsKeyDown(DIK_SPACE);
	isJumpPress = isJumpDown && !isPreviousJumpDown;
	isPreviousJumpDown = isJumpDown;


	isAttackDown = CKeyboard::getInstance()->IsKeyDown(DIK_Z);
	isAttackPress = isAttackDown && !isPreviousAttackDown;
	isPreviousAttackDown = isAttackDown;

	isPauseBoardDown = CKeyboard::getInstance()->IsKeyDown(DIK_P);
	isResumeBoardDown = CKeyboard::getInstance()->IsKeyDown(DIK_O);

	numberUpdate();
}

void KeyCheck::numberUpdate()
{
	isOneDown = CKeyboard::getInstance()->IsKeyDown(DIK_1);
	isOnePress = isOneDown && !isPreviousOne;
	isPreviousOne = isOneDown;

	isTwoDown = CKeyboard::getInstance()->IsKeyDown(DIK_2);
	isTwoPress = isTwoDown && !isPreviousTwo;
	isPreviousTwo = isTwoDown;

	isThreeDown = CKeyboard::getInstance()->IsKeyDown(DIK_3);
	isThreePress = isThreeDown && !isPreviousThree;
	isPreviousThree = isThreeDown;

	isFourDown = CKeyboard::getInstance()->IsKeyDown(DIK_4);
	isFourPress = isFourDown && !isPreviousFour;
	isPreviousFour = isFourDown;

	isFiveDown = CKeyboard::getInstance()->IsKeyDown(DIK_5);
	isFivePress = isFiveDown && !isPreviousFive;
	isPreviousFive = isFiveDown;

	isSixDown = CKeyboard::getInstance()->IsKeyDown(DIK_6);
	isSixPress = isSixDown && !isPreviousSix;
	isPreviousSix = isSixDown;

	isSevenDown = CKeyboard::getInstance()->IsKeyDown(DIK_7);
	isSevenPress = isSevenDown && !isPreviousSeven;
	isPreviousSeven = isSevenDown;

	isEightDown = CKeyboard::getInstance()->IsKeyDown(DIK_8);
	isEightPress = isEightDown && !isPreviousEight;
	isPreviousEight = isEightDown;

	isNineDown = CKeyboard::getInstance()->IsKeyDown(DIK_9);
	isNinePress = isNineDown && !isPreviousNine;
	isPreviousNine = isNineDown;

}

KeyCheck::KeyCheck()
{
	isPreviousLeftDown = false;
	isPreviousRightDown = false;
	isPreviousJumpDown = false;
	isPreviousMoveDown = false;
	isPreviousEnter = false;
	isPreviousOne = false;

}
KeyCheck::~KeyCheck()
{
}
