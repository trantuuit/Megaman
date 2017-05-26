#pragma once
#include"MGMSprite.h"

enum SPRITE_LIST
{
	//add
	SPR_STONE_DIE = -5,
	SPR_BOARD = -4,
	SPR_SCORE = -3,
	SPR_STAIRS = -2,
	SPR_GROUND = -1,
	SPR_MEGAMAN = 0,
	SPR_PICKETMAN = 1,
	SPR_OCTOPUSBATTERY = 2,
	SPR_BIGEYE = 3,
	SPR_FLYING_SHELL = 4,
	SPR_BLADER = 5,
	SPR_BEAK = 6,
	SPR_FLEA = 7,
	SPR_SCREWBOMBER = 8,
	SPR_CUTMAN = 9,

	SPR_HP = 10,
	SPR_ITEM_YASHICHI = 11,
	SPR_ITEM_UP = 12,
	SPR_ITEM_LIFE_ENERGY_SMALL = 13,	
	SPR_ITEM_LIFE_ENERGY_BIG = 14,
	SPR_ITEM_WEAPON_ENERGY_BIG = 15,
	SPR_ITEM_WEAPON_ENERGY_SMALL = 16,
	SPR_ITEM_BONUS_BALL = 17,
	SPR_CUTMANBULLET = 18,
	SPR_SUPER_CUTTER = 19,
	SPR_BEAK_BULLET = 20,
	SPR_BULLET = 21,
	SPR_DOOR = 22,
	SPR_MET=23,
	// Dung
	SPR_ROOM = 24,
	SPR_BOSS_GUTSMAN = 25,
	SPR_BIGROCK = 26,
	SPR_SMALLROCK = 27,
	SPR_GREENBAR = 28,
	SPR_DIE_AFFECT = 29,
	SPR_ARROW = 30,
	SPR_ITEM_EFFECT,
	SPR_PKM_WEAPON=32,
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

