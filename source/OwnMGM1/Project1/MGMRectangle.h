#pragma once
#include<Windows.h>
class MGMRectangle
{
public:
	float x, y;
	int width, height;
	MGMRectangle();
	RECT toRect();

	int getLeft();
	int getTop();
	int getRight();
	int getBottom();

	int getXCenter();
	int getYCenter();

	MGMRectangle(float x, float y, float width, float height);
	virtual void init(float x, float y, float width, float height);
	~MGMRectangle();
};

