#pragma once
#include"Keyboard.h"
class KEY
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

			isLeftPress,
			isRightPress,
			isJumpPress,

			isAttackDown,
			isPreviousAttackDown,
			isAttackPress,

			isMovePress,

			
			isPauseBoardDown,
			isResumeBoardDown;


	static KEY* instance;
	static KEY* getInstance();

	void update();

	KEY();
	~KEY();
};

