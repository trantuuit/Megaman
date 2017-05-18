#pragma once
#include "MGMEnemy.h"
#include"MGMDelayTime.h"
enum OCTOPUSBATTERY_ACTIVITY //Phân loại hoạt động
{
	OCTOPUSBATTERY_OPEN,
	OCTOPUSBATTERY_RUN_CLOSE,
	OCTOPUSBATTERY_CLOSE,
	
};
class OctopusBattery :
	public MGMEnemy
{

public:
	MGMDelayTime delayRunCloseActivity;
	MGMDelayTime delayCloseActivity;
	OCTOPUSBATTERY_ACTIVITY OctActivity;
	bool pauseAnimation;
	void update();
	void render();
	void onCollision(MGMBox *otherObject, int nx, int ny);
	OctopusBattery();
	~OctopusBattery();
};

