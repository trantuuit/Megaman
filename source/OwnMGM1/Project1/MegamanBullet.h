#pragma once
#include"List.h"
#include "MGMMovableObject.h"
class MegamanBullet :
	public MGMMovableObject
{
private:
	
	static List<MegamanBullet*>* bullets;
public:
	boolean isKill;
	static List<MegamanBullet*>* getBullets();
	MegamanBullet();
	void onCollision(MGMBox* other, int nx, int ny);
	~MegamanBullet();
};

