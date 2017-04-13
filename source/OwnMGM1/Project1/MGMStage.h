#pragma once
#include "MGMRectangle.h"
#include<fstream>
using namespace std;
class MGMStage :
	public MGMRectangle
{
public:
	static MGMStage* curStage;
	int index;
	static bool checkMegamanInStage(MGMRectangle* M, MGMRectangle* S);
	MGMStage(ifstream& fs);
	~MGMStage();
};

