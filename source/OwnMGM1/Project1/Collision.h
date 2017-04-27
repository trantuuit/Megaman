#pragma once
#include "MGMBox.h"

#define MAX(a,b) a>b? a:b
#define MIN(a,b) a>b? b:a

#define MINABS(a,b) abs(a)>abs(b)? b:a

class Collision
{
public:
	Collision();
	~Collision();

	static MGMBox* GetSweptBroadphaseBox(MGMBox* box);
	static bool AABBCheck(MGMRectangle* block, MGMRectangle* bigBox);
	static float SweptAABB(MGMBox* box1, MGMBox* box2, float &normalX, float &normalY);
	static void checkCollision(MGMBox*M, MGMBox*S);

	static void preventMove(MGMBox*M, MGMBox*S,int nx,int ny);

};

