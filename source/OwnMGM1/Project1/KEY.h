#pragma once
#include"Keyboard.h"
class KEY
{
public:
	bool	isLeftDown,
			isRightDown,
			isJumpDown,
			isMoveDown,

			isPreviousLeftDown,
			isPreviousRightDown,
			isPreviousJumpDown,
			isPreviousMoveDown,

			isLeftPress,
			isRightPress,
			isJumpPress,
			isMovePress;


	static KEY* instance;
	static KEY* getInstance();

	void update();

	KEY();
	~KEY();
};

