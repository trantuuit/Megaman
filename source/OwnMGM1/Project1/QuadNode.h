#pragma once
#include "MGMBox.h"
#include<fstream>
#include"MGMObject.h"
using namespace std;
class QuadNode :
	public MGMBox
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

