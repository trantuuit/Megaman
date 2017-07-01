#include "MGMObject.h"
#include"Collision.h"
#include"MGMCamera.h"
#include "BoardBar.h"
MGMObject::MGMObject()
{
	curAction = 0;
	curFrame = 0;
	timeFrame._tickPerFrame = 100;
	//ay = -0.005;
	//vy = -0.4;
	dx = 0;
	dy = 0;
	ax = 0;
	ay = GRAVITY;
	objectDirection = RIGHT;
}

void MGMObject::init(float x, float y, float width, float height)
{
	MGMBox::init(x, y, width, height);
	oldRect.init(x, y, width, height);
}

void MGMObject::restoreObject()
{
	x = oldRect.x;
	y = oldRect.y;
	isKill = false;
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
	if (timeFrame.at()) {

		int lastFrame = curFrame;

		//if(isUpdateFrameAnimation)
		this->sprite->Update(curAction, curFrame);

		if (lastFrame == this->sprite->animations[curAction]._framesCount - 1 && curFrame == 0)
			onLastFrameAnimation(curAction);
	}
}




void MGMObject::onCollision(MGMBox* otherObject, int nx, int ny)
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
	xDraw = (int)xDraw;
	yDraw = (int)yDraw;
	//Nếu hướng object khác hướng hình vẽ( hướng hình vẽ = left(-1))
	if (objectDirection != sprite->pImage->imageDirection)
	{
		int widthSprite = sprite->animations[curAction].frames[curFrame].width;
		//Lật x bằng cách nhân tất cả điểm ảnh cho ma trận bên dưới
		MGMEngine::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			2 * (xDraw + widthSprite / 2), 0, 0, 1)));
	}

	this->sprite->Render(xDraw, yDraw, curAction, curFrame);


	if (objectDirection != sprite->pImage->imageDirection)
	{
		MGMEngine::getInstance()->GetSprite()->SetTransform(&(D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1)));
	}
}

void MGMObject::vibrateRender()
{
	if (sprite == 0)
		return;
	float xDraw, yDraw;
	MGMCamera::getInstance()->Transform(x, y, xDraw, yDraw);

	switch (drawLocation)
	{
	case DRAW_LOCATION_1:
		this->sprite->Render(xDraw - 6, yDraw + 6, curAction, curFrame);
		drawPerLocation++;
		if (drawPerLocation >= drawCount)
		{
			drawLocation = DRAW_LOCATION_2;
			drawPerLocation = 0;
		}
		break;
	case DRAW_LOCATION_2:
		this->sprite->Render(xDraw + 4, yDraw - 4, curAction, curFrame);
		drawPerLocation++;
		if (drawPerLocation >= drawCount)
		{
			drawLocation = DRAW_LOCATION_3;
			drawPerLocation = 0;
		}

		break;
	case DRAW_LOCATION_3:
		MGMCamera::getInstance()->Transform(x + 8, y - 8, xDraw, yDraw);
		drawPerLocation++;
		if (drawPerLocation >= drawCount)
		{
			drawLocation = DRAW_LOCATION_4;
			drawPerLocation = 0;
		}
		break;
	case DRAW_LOCATION_4:
		MGMCamera::getInstance()->Transform(x - 4, y + 4, xDraw, yDraw);
		drawPerLocation++;
		if (drawPerLocation >= drawCount)
		{
			drawLocation = DRAW_LOCATION_5;
			drawPerLocation = 0;
		}
		break;
	case DRAW_LOCATION_5:
		MGMCamera::getInstance()->Transform(x - 8, y + 8, xDraw, yDraw);
		drawPerLocation++;
		if (drawPerLocation >= drawCount)
		{
			drawLocation = DRAW_LOCATION_6;
			drawPerLocation = 0;
		}
		break;
	case DRAW_LOCATION_6:
		MGMCamera::getInstance()->Transform(x, y - 10, xDraw, yDraw);
		drawPerLocation++;
		if (drawPerLocation >= drawCount)
		{
			drawLocation = DRAW_LOCATION_1;
			drawPerLocation = 0;
		}
		break;
	default:
		break;
	}
}


MGMObject::~MGMObject()
{
}
