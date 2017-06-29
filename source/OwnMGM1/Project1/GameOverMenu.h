#pragma once
#include"MGMSprite.h"
#include "MGMDelayTime.h"
class GameOverMenu
{
	MGMSprite* sprite1, *sprite2;
	int x, y;
	int curAction;
	int curFrame;
	MGMTexture * OpenScreen;
	static GameOverMenu* menu;
	MGMDelayTime delayAppearMenu, delayCloseMenu;
	int point1, point2, point3, point4, point5, point6, point7;
	
public:
	GameOverMenu();
	boolean isStart;
	boolean isOpen;
	static GameOverMenu* getInstance();
	void update();
	void render();
	~GameOverMenu();
};

