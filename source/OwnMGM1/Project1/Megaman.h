#pragma once
#include "MGMMovableObject.h"

enum MEGAMAN_ACTION
{
	MGM_STAND,
	MGM_PRE_RUN,
	MGM_RUN,
	MGM_JUMP
};

class Megaman :
	public MGMMovableObject
{
public:
	bool isOnGround;
	static Megaman* instance;
	static Megaman* getInstance();

	int action;

	/*Cập nhật vận tốc*/
	void update();
	void render();

	void setCurAction(int action);

	void onLastFrameAnimation(int action);



	void onCollision(MGMBox* other, int nx, int ny);

	Megaman();
	~Megaman();
};

