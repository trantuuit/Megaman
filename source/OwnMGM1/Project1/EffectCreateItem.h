#pragma once
#include"MGMSprite.h"
#include"MGMEnemy.h"
#include"MGMObject.h"
#include"MGMDelayTime.h"
enum ACTION_EFFECT_ITEM{
	ACTION_EFFECT_ITEM_FIRE,
	ACTION_EFFECT_ITEM_NONE,
};
class EffectCreateItem :public MGMObject
{
private:
	
	static EffectCreateItem* effect;
	bool isDraw;
public:
	MGMDelayTime timedelay;
	static EffectCreateItem* getInstance();
	MGMEnemy* enemy;
	ACTION_EFFECT_ITEM action;
	EffectCreateItem();
	void update();
	void render();
	~EffectCreateItem();
};

