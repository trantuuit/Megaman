#include "BoardBar.h"
#include"MGMSpriteManager.h"
#include"KEY.h"
#include "Megaman.h"
BoardBar* BoardBar::board = 0;
BoardBar* BoardBar::getInstance(){
	if (board == 0){
		board = new BoardBar();
	}
	return board;
}
BoardBar::BoardBar()
{
	this->sprite1 = MGMSpriteManager::getInstance()->sprites[SPR_BOARD];
	this->sprite2 = MGMSpriteManager::getInstance()->sprites[SPR_SCORE];
	curAction = 0;
	curFrame = 0;
	x = 120;
	y = 47;
	isPause = false;
	timeFrame.tickPerFrame = 100;
}
void BoardBar::update(){
	int life = Megaman::getInstance()->life;
	up1 = (life % 100) / 10;
	up2 = life % 10;
	if (KEY::getInstance()->isPauseBoardDown){
		isPause = true;
	}
	if (KEY::getInstance()->isResumeBoardDown){
		isPause = false;
	}
	updateAnimation();
}
void BoardBar::updateAnimation(){
	if (sprite1==0){
		return;
	}
	if (timeFrame.atTime()){
		this->sprite1->Update(curAction, curFrame);
	}
}
void BoardBar::render(){
	if (isPause){
		this->sprite1->Render(x, y, curAction, curFrame);
		this->sprite2->Render(185, 158, 0, up1);
		this->sprite2->Render(195, 158, 0, up2);
	}
	
}

BoardBar::~BoardBar()
{
}
