#pragma once
#include "MGMTexture.h"
#include"MGMBox.h"
#include"MGMObjectsCategory.h"
class MGMCamera: public MGMBox
{
private:
	static MGMCamera* instance;
public:
	MGMObjectsCategory objects;
	static MGMCamera* getInstance();
	void Transform(float x, float y, float& xRender, float& yRender);
	void update();
	MGMCamera();
	~MGMCamera();
};

