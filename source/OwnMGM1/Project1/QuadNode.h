#pragma once
#include "MGMRectangle.h"
#include<fstream>
#include"MGMObject.h"
using namespace std;
class QuadNode :
	public MGMRectangle
{
public:
	double id;
	int nObjects;
	MGMObject** objects;
	QuadNode* TL,* TR,* BL,* BR;
	QuadNode(ifstream& fs, MGMObject**allObjects,int heightMap);
	void fillObjectToCamera();
	~QuadNode();
};

