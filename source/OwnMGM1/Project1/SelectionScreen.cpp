#include "SelectionScreen.h"



SelectionScreen::SelectionScreen()
{
	this->OpenScreen = new MGMTexture("Data\\SelectionScreen.png",NULL);
	//this->selection = new SelectionRectangle();
	this->x = this->y = 0;
}

void SelectionScreen::render()
{
	OpenScreen->RenderTexture(x, y, 0);
}
SelectionScreen::~SelectionScreen()
{
	if (OpenScreen != NULL) delete OpenScreen;
	//if (selection != NULL) delete selection;;
}
