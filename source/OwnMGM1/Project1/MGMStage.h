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
	MGMStage(ifstream& fs);
	~MGMStage();
};

