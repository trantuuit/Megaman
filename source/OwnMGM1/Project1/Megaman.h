#pragma once
#include "MGMMovableObject.h"
class Megaman :
	public MGMMovableObject
{
public:
	bool isOnGround;
	static Megaman* instance;
	static Megaman* getInstance();
	/*Cập nhật vận tốc*/
	void update();
	void render();


	void onCollision(MGMBox* other, int nx, int ny);

	Megaman();
	~Megaman();
};

