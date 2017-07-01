#include "BoardBar.h"
#include"MGMSpriteManager.h"
#include"KEY.h"
#include "Megaman.h"
#include"MGMAudioManager.h"
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
	curActionFoMegaman = 1;
	curFrameForMegaman = 0;
	curActionForCut = 2;
	curFrameForcut = 0;
	x = 120;
	y = 47;
	isChooseCut = isChooseMega = false;
	isPause = false;
	timeFrame._tickPerFrame = 100;
}
void BoardBar::update(){
	int life = Megaman::getInstance()->life;
	up1 = (life % 100) / 10;
	up2 = life % 10;
	if (KEY::getInstance()->isPauseBoardDown){
		isPause = true;
		MGMAudioManager::getInstance()->Play(AUDIO_PAUSE_MENU);
		if (Megaman::getInstance()->isChangeCutMan){
			isChooseCut = true;
			isChooseMega = false;
		}
		else{
			isChooseMega = true;
			isChooseCut = false;
		}


	}
	if (KEY::getInstance()->isDownHold&&isPause){
		if (isChooseCut){
			isChooseMega = true;
			isChooseCut = false;
		}
	}
	if (KEY::getInstance()->isUpHold&&isPause){
		if (isChooseMega){
			isChooseCut = true;
			isChooseMega = false;
		}
	}
	if (KEY::getInstance()->isEnterDown && isPause){
		if (isChooseMega){
			Megaman::getInstance()->isChangeCutMan = false;
			isPause = false;
		}
		if (isChooseCut){
			Megaman::getInstance()->isChangeCutMan = true;
			isPause = false;
		}
	}
	updateAnimation();
}
void BoardBar::updateAnimation(){
	if (sprite1 == 0){
		return;
	}
	if (timeFrame.at()){
		this->sprite1->Update(curAction, curFrame);
		if (isChooseCut){
			this->sprite1->Update(curActionForCut, curFrameForcut);
		}
		if (isChooseMega){
			this->sprite1->Update(curActionFoMegaman, curFrameForMegaman);
		}

	}
}
void BoardBar::render(){
	if (isPause){
		this->sprite1->Render(x, y, curAction, curFrame);
		if (isChooseCut){
			this->sprite1->Render(x + 11, y + 62, curActionForCut, curFrameForcut);
		}
		else{
			this->sprite1->Render(x + 11, y + 62, curActionForCut, 0);
		}
		if (isChooseMega){
			this->sprite1->Render(x + 10, y + 107, curActionFoMegaman, curFrameForMegaman);
		}
		else{
			this->sprite1->Render(x + 10, y + 107, curActionFoMegaman, 0);
		}

		this->sprite2->Render(185, 158, 0, up1);
		this->sprite2->Render(195, 158, 0, up2);
	}

}

BoardBar::~BoardBar()
{
}
