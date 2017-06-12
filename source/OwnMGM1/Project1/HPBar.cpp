#include "HPBar.h"
#include"MGMSpriteManager.h"
#include"Megaman.h"
#include"BoardBar.h"
#include"BossGutsman.h"
#include"MGMAudioManager.h"
#include"BossCutMan.h"
HPBar* HPBar::hp = 0;
HPBar* HPBar::getInstance(){
	if (hp == 0){
		hp = new HPBar();
	}
	return hp;
}
HPBar::HPBar()
{
	this->sprite_MGM = MGMSpriteManager::getInstance()->sprites[SPR_HP_MEGAMAN];
	this->sprite_BOSS = MGMSpriteManager::getInstance()->sprites[SPR_HP_BOSS];
	curAction = 0;
	curFrame_MG = 0;
	curFrame_Boss = 0;
	x = 10;
	y = 10;
}

void HPBar::update(){
	if (Megaman::getInstance()->healthPoint >= 0){
		int healthPoint = Megaman::getInstance()->healthPoint;
		if (healthPoint > curFrame_MG){
			curFrame_MG++;
			MGMAudioManager::getInstance()->Play(AUDIO_ENERGY_FILL);
		}
		else{
			curFrame_MG = healthPoint;
		}
	}
	else{
		curFrame_MG = 0;
	}
	if (BossGutsman::getInstance()->appearHP){
		if (BossGutsman::getInstance()->healthPoint >= 0){
			int healthPoint = BossGutsman::getInstance()->healthPoint;
			if (healthPoint > curFrame_Boss){
				curFrame_Boss++;
				MGMAudioManager::getInstance()->Play(AUDIO_ENERGY_FILL);
			}
			else{
				curFrame_Boss = healthPoint;
			}
		}
		else{
			curFrame_Boss = 0;
		}
	}
	if (BossCutMan::getInstance()->appearHP){
		if (BossCutMan::getInstance()->healthPoint >= 0){
			int healthPoint = BossCutMan::getInstance()->healthPoint;
			if (healthPoint > curFrame_Boss){
				curFrame_Boss++;
				MGMAudioManager::getInstance()->Play(AUDIO_ENERGY_FILL);
			}
			else{
				curFrame_Boss = healthPoint;
			}

		}
		else{
			curFrame_Boss = 0;
		}
	}
}
void HPBar::render(){
	this->sprite_MGM->Render(x, y, curAction, curFrame_MG);
	if (BossGutsman::getInstance()->appearHP || BossCutMan::getInstance()->appearHP){
		this->sprite_BOSS->Render(x + 10, y, curAction, curFrame_Boss);
	}

}

HPBar::~HPBar()
{
}
