#include "MGMAnimation.h"
extern void LineDown(ifstream& fs, int lineCount);

MGMAnimation::MGMAnimation()
{
}

MGMAnimation::MGMAnimation(ifstream& fs){
	init(fs);

}

void MGMAnimation::init(ifstream& fs)
{
	 LineDown(fs, 6);
	fs >> this->_framesCount;
	 LineDown(fs, 4);
	this->frames = new MGMBox[_framesCount];
	for (int i = 0; i < _framesCount; i++){
		fs >> frames[i].x >> frames[i].y >> frames[i].width >> frames[i].height;
	}
	 LineDown(fs, 1);
}


MGMAnimation::~MGMAnimation()
{
	if (frames != NULL)
		delete[]frames;
}
void MGMAnimation::nextFrame(int& curFrame){
	if (curFrame >= _framesCount - 1){
		curFrame = 0;
	}
	else{
		curFrame++;
	}
}
