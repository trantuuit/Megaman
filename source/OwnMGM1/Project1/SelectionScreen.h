#pragma once
#include"SelectionRectangle.h"
class SelectionScreen
{
public:
	int x;
	int y;
	MGMTexture * OpenScreen;
	//SelectionRectangle *selection;
	SelectionScreen();                 
	void render();
	~SelectionScreen();
};

