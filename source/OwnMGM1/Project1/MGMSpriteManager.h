#pragma once
#include"MGMSprite.h"

enum SPRITE_LIST
{
	//add
	SPR_STAIRS = -2,
	SPR_GROUND = -1,
	SPR_OCTOPUSBATTERY = 28,
	SPR_PICKETMAN = 1,
	SPR_MEGAMAN,
	SPR_BIGEYE,
	SPR_BULLET,
	SPR_BLADER=9,
	SPR_BEAK=5,
	SPR_BEAK_BULLET = 99,
	SPR_FLEA,
	SPR_COUNT
};

class MGMSpriteManager
{
	static MGMSpriteManager* instance;
public:
	static MGMSpriteManager* getInstance();

	MGMSprite** sprites;
	MGMSpriteManager();
	~MGMSpriteManager();
};

