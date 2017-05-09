#pragma once
#include"MGMSprite.h"

enum SPRITE_LIST
{
	//add
	
	SPR_BEAK_BULLET = -5,     
	SPR_BULLET=-4,
	SPR_DOOR = -3,
	SPR_STAIRS = -2,
	SPR_GROUND = -1,
	SPR_MEGAMAN = 0,
	SPR_PICKETMAN = 1,
	SPR_OCTOPUSBATTERY = 2,
	SPR_BIGEYE = 3,
	SPR_FLYING_SHELL = 4,
	SPR_BLADER = 5,
	SPR_BEAK=6,
	SPR_FLEA=7,
	SPR_SCREWBOMBER = 8,
	SPR_SUPER_CUTTER =9,
	
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

