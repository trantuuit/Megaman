#pragma once
#include "MGMEnemy.h"
#include "List.h"
class SmallRock :
	public MGMEnemy
{
	static List<SmallRock*> *smallRocks;
public:
	static List<SmallRock*>* getSmallRocks();
	SmallRock();
	void init(int x, int y, int w, int h);
	~SmallRock();
};

