#pragma once
#include"MGMObject.h"
#include"MGMSpriteManager.h"
#include"PicketMan.h"
#include "MGMMap.h"
#include"Megaman.h"
#include "MGMCamera.h"

class MGMGame
{
private:
	MGMObject M;
	MGMTexture text;
	int nStage;
	int objectDirection;
	static MGMGame *instance;
	int ObjectCount;
public:
	MGMMap *map;
	MGMMap *mapCut;
	MGMMap *mapGut;
	bool isStart;
	static MGMGame *getInstance();
	void init();
	void update(DWORD timesleep);
	void render();
	MGMGame();
	~MGMGame();
};

