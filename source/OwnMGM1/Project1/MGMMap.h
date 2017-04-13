#pragma once
#include "MGMTileMap.h"
#include"MGMObject.h"
#include"QuadTree.h"
#include"MGMStage.h"
#include<fstream>
#include"MGMBox.h"
using namespace std;
class MGMMap :
	public MGMTileMap
{
public:
	int nObject;
	bool isUpdate;
	QuadTree* quadTree;
	int nStage;
	MGMObject** allObjects;
	MGMStage** stages;
	bool isChangeStage;

	/*Đọc object và tạo sprite cho object*/
	void readObjects(char* objectsPath);

	void readStage(char* stagePath);
	void updateStage();
	void update();
	void draw();

	MGMMap(char* objectsPath,char* tileSheetPath,char* quadTreePath,char* matrixPath,char* stagePath);
	~MGMMap();
};

