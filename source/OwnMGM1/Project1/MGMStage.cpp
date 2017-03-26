#include "MGMStage.h"


MGMStage* MGMStage::curStage = 0;


MGMStage::MGMStage(ifstream & fs)
{
	fs >> x >> y >> width >> height;
}


MGMStage::~MGMStage()
{
}
