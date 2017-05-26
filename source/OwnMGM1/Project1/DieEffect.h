#pragma once
#include "MGMMovableObject.h"
#include "MGMSprite.h"
#include"List.h"
enum AFFECT_CATEGORY{
	MEGAMAN_DIE,
	CUTMAN_DIE,
	GUTMAN_DIE,
};
class DieAffect :
	public MGMMovableObject
{
private:
	static List<DieAffect*>* list;
public:
	static List<DieAffect*>* getList();
	DieAffect();
	DieAffect(AFFECT_CATEGORY);
	~DieAffect();
};

