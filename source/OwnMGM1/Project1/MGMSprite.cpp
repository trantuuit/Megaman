#include "MGMSprite.h"

extern void LineDown(ifstream& fs, int lineCount);
MGMSprite::MGMSprite(char* infor, char* imagepath)
{
	ifstream fs(infor);
	 LineDown(fs, 1);
	int r, g, b;
	fs >> r >> g >> b;
	pImage = new MGMTexture(imagepath, D3DCOLOR_XRGB(r, g, b));

	 LineDown(fs, 2);
	fs >> this->animationCount;
	 LineDown(fs, 1);

	this->animations = new MGMAnimation[this->animationCount];
	for (int i = 0; i < animationCount; i++) {
		animations[i].init(fs);
	}

}

void MGMSprite::initInfoFromPath(char* infor)
{
	ifstream fs(infor);
	 LineDown(fs, 1);
	int r, g, b;
	fs >> r >> g >> b;

	 LineDown(fs, 2);
	fs >> this->animationCount;
	 LineDown(fs, 1);

	this->animations = new MGMAnimation[this->animationCount];
	for (int i = 0; i < animationCount; i++) {
		animations[i].init(fs);
	}
	fs.close();
}


void MGMSprite::Update(int curAction, int& curFrame)
{
	 animations[curAction].nextFrame(curFrame);
}
void MGMSprite::Render(float x, float y, int curAction, int curFrame)
{
	MGMAnimation* ani = &animations[curAction];
	pImage->RenderTexture(x, y, &ani->frames[curFrame].toRect());
}

MGMSprite::MGMSprite()
{
}

MGMSprite::~MGMSprite()
{
	if (pImage != NULL) delete pImage;
	if (animations != NULL)delete[]animations;
}
