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
	static bool checkMegamanInStage(MGMRectangle* M, MGMRectangle* S);// phuc vu cho viec chuyen stage
	static bool checkObjectInStage(MGMRectangle* M, MGMRectangle* S); // phuc vu viec fix loi nhay cham gach
	MGMStage(ifstream& fs);
	~MGMStage();
};

