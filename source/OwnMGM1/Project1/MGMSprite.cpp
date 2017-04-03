#include "MGMSprite.h"

extern void ignoreLineIfstream(ifstream& fs, int lineCount);
MGMSprite::MGMSprite(char* infor, char* imagepath)
{
	ifstream fs(infor);
	ignoreLineIfstream(fs, 1);
	int r, g, b;
	fs >> r >> g >> b;
	pImage = new MGMTexture(imagepath, D3DCOLOR_XRGB(r, g, b));

	ignoreLineIfstream(fs, 2);
	fs >> this->animationCount;
	ignoreLineIfstream(fs, 1);

	this->animations = new MGMAnimation[this->animationCount];
	for (int i = 0; i < animationCount; i++) {
		animations[i].init(fs);
	}

}

void MGMSprite::initInfo(char* infor)
{
	ifstream fs(infor);
	ignoreLineIfstream(fs, 1);
	int r, g, b;
	fs >> r >> g >> b;

	ignoreLineIfstream(fs, 2);
	fs >> this->animationCount;
	ignoreLineIfstream(fs, 1);

	this->animations = new MGMAnimation[this->animationCount];
	for (int i = 0; i < animationCount; i++) {
		animations[i].init(fs);
	}
	fs.close();
}


void MGMSprite::Update(int curAction, int& curFrame)
{
	 animations[curAction].next(curFrame);
}
void MGMSprite::Render(int x, int y, int curAction, int curFrame)
{
	MGMAnimation* ani = &animations[curAction];
	pImage->RenderTexture(x, y, &ani->frames[curFrame].toRect());
}

MGMSprite::~MGMSprite()
{
}
