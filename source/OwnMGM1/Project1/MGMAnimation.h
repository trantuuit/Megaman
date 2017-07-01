#pragma once
#include"MGMGameTime.h"
#include "MGMBox.h"
#include "MGMTexture.h"
#include<fstream>
using namespace std;
class MGMAnimation
{
public:
	int _framesCount;
	MGMBox* frames;
	MGMAnimation();
	MGMAnimation(ifstream& fs);
	void init(ifstream& fs);
	~MGMAnimation();
	void nextFrame(int& curFrame);
};