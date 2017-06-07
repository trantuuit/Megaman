#pragma once
#include "MGMMovableObject.h"

class Blink :
	public MGMMovableObject

{
	int renderFrameCount;
	int NotRenderFrameCount;
public:
	static Blink* instance;
	bool isRender;
	static Blink* getInstance();
	void render();
	Blink();
	~Blink();
};

