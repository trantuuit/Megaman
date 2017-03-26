#pragma once
#include"MGMGameTime.h"
#include "MGMRectangle.h"
#include "MGMTexture.h"
#include<fstream>
using namespace std;
class MGMAnimation
{
public:

	int framesCount; //Số frame của animation
	MGMRectangle* frames;
	MGMAnimation();
	MGMAnimation(ifstream& fs);
	void init(ifstream& fs);
	~MGMAnimation();
	void next(int& curFrame);
};