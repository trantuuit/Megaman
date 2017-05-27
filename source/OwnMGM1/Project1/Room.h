﻿#pragma once
#include "MGMEnemy.h"
class Room :
	public MGMEnemy
{
	int ActionCount;
	static Room* room;
public:
	static Room* getInstance();
	static bool isVibrate; // Biến thiết lập rung hoặc không
	int vibrateCount; // Số frame trong 1 lần rung

	Room();
	void update();
	void render();
	~Room();
};

	