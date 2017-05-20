#pragma once
#include "MGMEnemy.h"
#include"List.h"
#include"MGMSpriteManager.h"
#include "MGMDelayTime.h"

enum Location
{
	LOCATION_1,
	LOCATION_2
};
class SuperCutter :
	public MGMEnemy
{
	static List<SuperCutter*> *superCutters;
	/*float dx, dy;*/
public:
	static Location location;
	static MGMDelayTime timeDelay;
	static bool isAppear();
	static List<SuperCutter*>* getSuperCutters();
	SuperCutter();
	SuperCutter(int x, int y, int w, int h);
	void deltaUpdate();
	~SuperCutter();
};

