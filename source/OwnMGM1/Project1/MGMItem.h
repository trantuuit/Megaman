#pragma once
#include "MGMMovableObject.h"
#include"List.h"
class MGMItem :
	public MGMMovableObject
{
	static List<MGMItem*>* listItem;
public:
	static List<MGMItem*>* getListItem();
	void onCollision(MGMBox* other, int nx, int ny);
	MGMItem();
	~MGMItem();
};

