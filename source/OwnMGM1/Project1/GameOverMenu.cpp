#include "GameOverMenu.h"
#include"MGMSpriteManager.h"
#include"Megaman.h"
#include "KEY.h"
#include"MGMGame.h"
GameOverMenu* GameOverMenu::menu = 0;
GameOverMenu* GameOverMenu::getInstance(){
	if (menu == 0){
		menu = new GameOverMenu();
	}
	return menu;
}
GameOverMenu::GameOverMenu()
{
	this->OpenScreen = new MGMTexture("Data\\Animation\\Gameover\\gameover.png", NULL);
	this->sprite1 = MGMSpriteManager::getInstance()->sprites[SPR_ARROW];
	this->sprite2 = MGMSpriteManager::getInstance()->sprites[SPR_SCORE];
	curAction = 0;
	curFrame = 0;
	isOpen = false;
	isStart = false;
	x = 54;
	y = 117;
}

void GameOverMenu::update(){
	if (Megaman::getInstance()->isKill){
		if (delayAppearMenu.isReady()&&delayAppearMenu.isFinish()){
			delayAppearMenu.start(5000);
		}
		if (delayAppearMenu.isFinish()){

			isOpen = true;
		}	
	}
	if (isOpen){
		if (KEY::getInstance()->isDownHold){
			if (!(x == 54 && y == 141)){
				x = 54;
				y = 141;
			}

		}
		if (KEY::getInstance()->isUpHold){
			if (!(x == 54 && y == 117)){
				x = 54;
				y = 117;
			}
		}
		if (KEY::getInstance()->isJumpDown){
			if (x == 54 && y == 141){
				MGMGame::getInstance()->isStart = true;
				
			}
			isOpen = false;
			Megaman::getInstance()->isKill = false;
			Megaman::getInstance()->healthPoint = 28;
			Megaman::getInstance()->beingAttacked = false;
		}
		int score = Megaman::getInstance()->score;
		point1 = score / 1000000;
		point2 = (score % 1000000) / 100000;
		point3 = (score % 100000) / 10000;
		point4 = (score % 10000) / 1000;
		point5 = (score % 1000) / 100;
		point6 = (score % 100) / 10;
		point7 = score % 10;
	}
	delayAppearMenu.update();
}
void GameOverMenu::render(){
	if (isOpen){
		OpenScreen->RenderTexture(0, 0, 0);
		sprite1->Render(x, y, curAction, curFrame);
		this->sprite2->Render(90, 55, 0, point1);
		this->sprite2->Render(100, 55, 0, point2);
		this->sprite2->Render(110, 55, 0, point3);
		this->sprite2->Render(120, 55, 0, point4);
		this->sprite2->Render(130, 55, 0, point5);
		this->sprite2->Render(140, 55, 0, point6);
		this->sprite2->Render(150, 55, 0, point7);
	}
}
GameOverMenu::~GameOverMenu()
{
}