#include "MGMAnimation.h"
extern void ignoreLineIfstream(ifstream& fs, int lineCount);

MGMAnimation::MGMAnimation()
{
}

MGMAnimation::MGMAnimation(ifstream& fs){
	init(fs);

}

void MGMAnimation::init(ifstream& fs)
{
	ignoreLineIfstream(fs, 6);
	fs >> this->framesCount;
	ignoreLineIfstream(fs, 4);
	this->frames = new MGMRectangle[framesCount];
	for (int i = 0; i < framesCount; i++){
		fs >> frames[i].x >> frames[i].y >> frames[i].width >> frames[i].height;
	}
	ignoreLineIfstream(fs, 1);
}


MGMAnimation::~MGMAnimation()
{
	if (frames != NULL)
		delete[]frames;
}
void MGMAnimation::next(int& curFrame){
	if (curFrame >= framesCount - 1){
		curFrame = 0;
	}
	else{
		curFrame++;
	}
}
