#include "MGMObject.h"
#include"Collision.h"
#include"MGMCamera.h"
MGMObject::MGMObject()
{
	curAction = 0;
	curFrame = 0;
	timeFrame.tickPerFrame = 100;

	//ay = -0.005;
	//vy = -0.4;
	dx = 0;
	dy = 0;
	ax = 0;
	ay = GRAVITY;
	objectDirection = RIGHT;
	isUpdateFrameAnimation = true;

}

void MGMObject::init(float x, float y, float width, float height)
{
	MGMRectangle::init(x, y, width, height);
	oldRect.init(x, y, width, height);
}

void MGMObject::restoreObject()
{
	x = oldRect.x;
	y = oldRect.y;
}

void MGMObject::setCurAction(int curAction)
{
	if (this->curAction != curAction)
	{
		this->curFrame = 0;
		this->curAction = curAction;
	}
}




void MGMObject::updateFrameAnimation() // this
{
	if (sprite == 0)
		return;
	MGMBox::update();
	//updateMove();
	if (timeFrame.atTime()) {

		int lastFrame = curFrame;

		if(isUpdateFrameAnimation)
			this->sprite->Update(curAction, curFrame);

		if (lastFrame == this->sprite->animations[curAction].framesCount - 1 && curFrame == 0)
			onLastFrameAnimation(curAction);
	}
}




void MGMObject::onCollision(MGMBox* other, int nx, int ny)
{

}

void MGMObject::onLastFrameAnimation(int action)
{
}


void MGMObject::update()
{
}

void MGMObject::render()
{
	if (sprite == 0)
		return;
	float xDraw, yDraw;
	MGMCamera::getInstance()->Transform(x, y, xDraw, yDraw);
	//Nếu hướng object khác hướng hình vẽ( hướng hình vẽ = left(-1))
	if (objectDirection != sprite->pImage->imageDirection)
	{
		int widthSprite = sprite->animations[curAction].frames[curFrame].width;
		//Lật x bằng cách nhân tất cả điểm ảnh cho ma trận bên dưới
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			2 * (xDraw + widthSprite / 2), 0, 0, 1)));
	}

	this->sprite->Render(xDraw, yDraw, curAction, curFrame);

	if (objectDirection != sprite->pImage->imageDirection)
	{
		MGMDirectXTool::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)));
	}
}


MGMObject::~MGMObject()
{
}
