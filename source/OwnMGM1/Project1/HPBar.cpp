#include "HPBar.h"
#include"MGMSpriteManager.h"
#include"Megaman.h"
#include"BoardBar.h"
HPBar* HPBar::hp = 0;
HPBar* HPBar::getInstance(){
	if (hp == 0){
		hp = new HPBar();
	}
	return hp;
}
HPBar::HPBar()
{
	this->sprite = MGMSpriteManager::getInstance()->sprites[SPR_HP];
	curAction = 0;
	curFrame = 0;
	x = 10;
	y = 10;
}

void HPBar::update(){
	if (Megaman::getInstance()->healthPoint >= 0){
		curFrame = Megaman::getInstance()->healthPoint;
	}
	else{
		curFrame = 0;
	}
}
void HPBar::render(){
		this->sprite->Render(x, y, curAction, curFrame);
}

HPBar::~HPBar()
{
}
