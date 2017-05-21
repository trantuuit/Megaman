#include "ScoreBar.h"
#include"MGMSpriteManager.h"
#include"Megaman.h"
ScoreBar* ScoreBar::score = 0;
ScoreBar* ScoreBar::getInstance(){
	if (score == 0){
		score = new ScoreBar();
	}
	return score;
}
ScoreBar::ScoreBar()
{
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_SCORE];
	curAction = 0;
	curFrame = 0;
	point1 = point2 = point3 = point4 = point5 = point6 = point7 = 0;
}

void ScoreBar::update(){
	//if (Megaman::getInstance()->healthPoint >= 0){
	//	curFrame = Megaman::getInstance()->healthPoint;
	//}
	//else{
	//	curFrame = 0;
	//}
	int score = Megaman::getInstance()->score;
	point1 = score / 1000000;
	point2 = (score % 1000000) / 100000;
	point3 = (score % 100000) / 10000;
	point4 = (score % 10000) / 1000;
	point5 = (score % 1000) / 100;
	point6 = (score % 100)/10;
	point7 = score % 10;

}
void ScoreBar::render(){
	this->sprite->Render(100, 10, curAction, point1);
	this->sprite->Render(110, 10, curAction, point2);
	this->sprite->Render(120, 10, curAction, point3);
	this->sprite->Render(130, 10, curAction, point4);
	this->sprite->Render(140, 10, curAction, point5);
	this->sprite->Render(150, 10, curAction, point6);
	this->sprite->Render(160, 10, curAction, point7);
}

ScoreBar::~ScoreBar()
{
}
