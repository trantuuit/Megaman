#pragma once
#include "MGMMovableObject.h"
#include"List.h"
#include "MGMDelayTime.h"
class MGMItem :
	public MGMMovableObject
{
private:
	static List<MGMItem*>* listItem;
	MGMDelayTime timeDie;
public:
	static List<MGMItem*>* getListItem();
	void onCollision(MGMBox* other, int nx, int ny);
	void CountDownDie();
	void update();
	void onInterserct(MGMBox* other);
	MGMItem();
	~MGMItem();
};

