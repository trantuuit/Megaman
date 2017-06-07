#pragma once
#include"MGMSprite.h"
class HPBar
{
private:
	MGMSprite* sprite_MGM;
	MGMSprite* sprite_BOSS;
	int x, y;
	int curAction;
	int curFrame_MG;
	int curFrame_Boss;
	static HPBar* hp;
	HPBar();
public:
	static HPBar* getInstance();
	void update();
	void render();
	~HPBar();
};

