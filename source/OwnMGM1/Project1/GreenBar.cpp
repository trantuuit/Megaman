#include "GreenBar.h"



GreenBar::GreenBar()
{
	ay = 0;
	vy = 0;
	timeFrame = 100;
	pauseAnimation = true;
	objectDirection = LEFT;
	dx = greenBarDx;
	categoryEnemy = GREEN_BAR;
}

void GreenBar::update()
{

	// Giới hạn 2 bên:
	if (y == 1124) // Thanh GreenBar thứ nhất
	{
		if (x <= 500){
			dx = greenBarDx;
			
		}
			
		if (x >= 772){
			dx = -greenBarDx;
			
		}
			
		pauseAnimation = true;
	}
	if (y == 1060) // Thanh GreenBar thứ hai
	{
		if (x <= 628){
			dx = greenBarDx;
		}
			
		if (x >= 900){
			dx = -greenBarDx;
		}
			
		if ((x >= 733 && x <= 749) || (x >= 861 && x <= 876))
			pauseAnimation = false;
		else
			pauseAnimation = true;
	}
	if (y == 996) // Thanh GreenBar thứ ba
	{
		if (x <= 756){
			
			dx = greenBarDx;
		}
			
		if (x >= 1108){
			
			dx = -greenBarDx;
		}
			
		if ((x >= 813 && x <= 828) || (x >= 876 && x <= 893)
			|| (x >= 940 && x <= 955) || (x >= 1004 && x <= 1020) || (x >= 1069 && x <= 1084))
			pauseAnimation = false;
		else
			pauseAnimation = true;
	}

	if (pauseAnimation == false)
		MGMMovableObject::updateFrameAnimation();
	else
		curFrame = 0;
}


void GreenBar::render()
{
	MGMEnemy::render();
}

GreenBar::~GreenBar()
{
}
