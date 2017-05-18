#pragma once
#include"MGMSprite.h"
class HPBar
{
private:
	MGMSprite* sprite;
	int x, y;
	int curAction;
	int curFrame;
	static HPBar* hp;
	HPBar();
public:
	static HPBar* getInstance();
	void update();
	void render();
	~HPBar();
};

