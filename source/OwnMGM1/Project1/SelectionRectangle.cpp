#include "SelectionRectangle.h"
#include"KEY.h"
#include"MGMGame.h"
#include"MGMAudioManager.h"
#include"BossCutMan.h"
#include"BossGutsman.h"
#include"Megaman.h"
void SelectionRectangle::update()
{
	if (MGMGame::getInstance()->isStart) {
		MGMAudioManager::getInstance()->LoopSound(AUDIO_SELECT_STAGE);
	}
	if (KEY::getInstance()->isMovePress)
	{
		if (x == 55)
		{
			x = 153;
			boss = GutsMan;

			MGMAudioManager::getInstance()->Play(AUDIO_MENU_SELECT);
		}
		else if (x == 153)
		{
			x = 55;
			boss = CutMan;

			MGMAudioManager::getInstance()->Play(AUDIO_MENU_SELECT);
		}

	}
	this->updateFrameAnimation();
	if (MGMGame::getInstance()->isStart) {
		if (KEY::getInstance()->isEnterPress)
		{
			MGMAudioManager::getInstance()->StopSound(AUDIO_SELECT_STAGE);
			MGMAudioManager::getInstance()->Play(AUDIO_GAME_START);
			MGMGame::getInstance()->isStart = false;
			if (boss == CutMan) {
				if (Megaman::getInstance()) {
					if (Megaman::getInstance()->isKill) {
						Megaman::getInstance()->reset();
						MGMGame::getInstance()->map = MGMGame::getInstance()->mapCut;
					}
					else {
						MGMGame::getInstance()->map = MGMGame::getInstance()->mapCut;
					}
				}			
			}
			else {
				if (Megaman::getInstance()) {
					if (Megaman::getInstance()->isKill) {
						Megaman::getInstance()->reset();
						MGMGame::getInstance()->map = MGMGame::getInstance()->mapGut;
					}
					else {
						MGMGame::getInstance()->map = MGMGame::getInstance()->mapGut;
					}
				}
				
			}
				
		}
	}

}

void SelectionRectangle::render()
{
	this->sprite->Render(x, y, curAction, curFrame);
}

SelectionRectangle::SelectionRectangle()
{
	this->sprite = new MGMSprite("Data\\Animation\\Selection Rectangle\\SelectionRectangle.txt", "Data\\Animation\\Selection Rectangle\\SelectionRectangle.png");
	x = 55;
	y = 80;
	boss = CutMan;
}


SelectionRectangle::~SelectionRectangle()
{
}
