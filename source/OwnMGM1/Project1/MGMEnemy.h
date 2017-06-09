#pragma once
#include "MGMMovableObject.h"
enum CATEGORY_ENEMY{
	CREP_BEAK,
	CREP_BLADER,
	CREP_BIG_EYE,
	CREP_FLEA,
	CREP_FLYING_SHELL,
	CREP_OCTOPUS_BATTERY,
	CREP_PICKET_MAN,
	CREP_SCREW_BOMBER,
	CREP_SUPER_CUTTER,
	CREP_MET,
	DEATH_LAND,
	GREEN_BAR,
	BOSS_GUTMAN,
	ROOM,
	BIG_ROCK,
	SMALL_ROCK,
	PKM_WEAPON,
	BOSS_CUTMAN,
	CUTMAN_WEAPON,
};
class MGMEnemy :
	public MGMMovableObject
{
public:

	CATEGORY_ENEMY categoryEnemy;
	int count;
	MGMEnemy();
	~MGMEnemy();
};

