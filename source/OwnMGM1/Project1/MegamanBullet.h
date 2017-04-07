#pragma once
#include"List.h"
#include "MGMMovableObject.h"
class MegamanBullet :
	public MGMMovableObject
{
	static List<MegamanBullet*>* bullets;
public:
	static List<MegamanBullet*>* getBullets();
	MegamanBullet();
	~MegamanBullet();
};

