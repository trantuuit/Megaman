#include "MGMStage.h"
#include"Megaman.h"

MGMStage* MGMStage::curStage = 0;



bool MGMStage::checkMegamanInStage(MGMBox* M, MGMBox* S)
{
	return ((M->getLeft() <= S->getRight() && M->getRight() >= S->getLeft()) &&
		(M->getYCenter() <= S->getTop() && M->getYCenter() >= S->getBottom()+5));
}

bool MGMStage::checkObjectInStage(MGMBox * M, MGMBox * S)
{
	return ((M->getLeft() <= S->getRight() && M->getRight() >= S->getLeft()) &&
		(M->getBottom() <= S->getTop() && M->getTop() >= S->getBottom()));
}

MGMStage::MGMStage(ifstream & fs)
{
	fs >> x >> y >> width >> height;
}


MGMStage::~MGMStage()
{
}
