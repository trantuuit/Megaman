#pragma once
#include"MGMSprite.h"
class BoardBar
{
private:
	MGMSprite* sprite1;
	MGMSprite* sprite2;
	int curAction;
	int curFrame;
	int x, y;
	static BoardBar* board;
	MGMGameTime timeFrame;
	int up1, up2;
public:
	BoardBar();
	boolean isPause;
	static BoardBar* getInstance();
	void update();
	void updateAnimation();
	void render();
	~BoardBar();
};

