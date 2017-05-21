#pragma once
#include"MGMSprite.h"
class ScoreBar
{
private:
	MGMSprite* sprite;
	int curAction;
	int curFrame;
	int point1, point2, point3, point4, point5, point6, point7;
	static ScoreBar* score;
public:
	ScoreBar();
	static ScoreBar* getInstance();
	void update();
	void render();
	~ScoreBar();
};

