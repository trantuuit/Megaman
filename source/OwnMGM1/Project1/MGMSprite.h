#pragma once
#include<fstream>
#include "MGMTexture.h"
#include "MGMAnimation.h"
using namespace std;
class MGMSprite
{
public:
	int animationCount;

	MGMTexture *pImage;
	MGMAnimation* animations;
	void Update(int curAction, int& curFrame);
	void Render(float x, float y, int curAction, int curFrame);
	MGMSprite();
	MGMSprite(char* infor, char* imagepath);

	void initInfoFromPath(char* infor);

	~MGMSprite();
};