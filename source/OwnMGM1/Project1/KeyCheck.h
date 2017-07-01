#pragma once
#include"Keyboard.h"
class KeyCheck
{
public:
	bool	isLeftDown,
		isUpHold,
		isDownHold,
		isRightDown,
		isJumpDown,
		isMoveDown,
		isEnterDown,

		isPreviousLeftDown,
		isPreviousRightDown,
		isPreviousJumpDown,
		isPreviousMoveDown,
		isPreviousEnter,


		isLeftPress,
		isRightPress,
		isJumpPress,
		isEnterPress,

		isAttackDown,
		isPreviousAttackDown,
		isAttackPress,

		isMovePress,


		isPauseBoardDown,
		isResumeBoardDown,

		isOneDown,
		isPreviousOne,
		isOnePress,

		isTwoDown,
		isPreviousTwo,
		isTwoPress,

		isThreeDown,
		isPreviousThree,
		isThreePress,

		isFourDown,
		isPreviousFour,
		isFourPress,

		isFiveDown,
		isPreviousFive,
		isFivePress,

		isSixDown,
		isPreviousSix,
		isSixPress,

		isSevenDown,
		isPreviousSeven,
		isSevenPress,

		isEightDown,
		isPreviousEight,
		isEightPress,

		isNineDown,
		isPreviousNine,
		isNinePress;
		

	static KeyCheck* instance;
	static KeyCheck* getInstance();

	void update();
	void numberUpdate();

	KeyCheck();
	~KeyCheck();
};

