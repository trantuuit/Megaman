#include "MGMStage.h"
#include"Megaman.h"

MGMStage* MGMStage::curStage = 0;



bool MGMStage::checkMegamanInStage(MGMRectangle* M, MGMRectangle* S)
{
	return ((M->getLeft() <= S->getRight() && M->getRight() >= S->getLeft()) &&
		(M->getYCenter() <= S->getTop() && M->getYCenter() >= S->getBottom()+3));
}

MGMStage::MGMStage(ifstream & fs)
{
	fs >> x >> y >> width >> height;
}


MGMStage::~MGMStage()
{
}
