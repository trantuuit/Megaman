#pragma once
#include "MGMBox.h"
#include<fstream>
using namespace std;
class MGMStage :
	public MGMBox
{
public:
	static MGMStage* curStage;
	int index;
	static bool checkMegamanInStage(MGMBox* M, MGMBox* S);// phuc vu cho viec chuyen stage
	static bool checkObjectInStage(MGMBox* M, MGMBox* S); // phuc vu viec fix loi nhay cham gach
	MGMStage(ifstream& fs);
	~MGMStage();
};

