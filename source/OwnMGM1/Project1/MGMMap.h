#pragma once
#include "MGMTileMap.h"
#include"MGMObject.h"
#include"QuadTree.h"
#include"MGMStage.h"
#include<fstream>
#include"MGMBox.h"
#include"Door.h"
#include"KeyCheck.h"
using namespace std;

enum BossMap
{
	CutMap,
	GutsMap
};
class MGMMap :
	public MGMTileMap
{
public:
	int nObject;
	bool isUpdate;
	BossMap bossMap;
	QuadTree* quadTree;
	D3DXVECTOR2 * positionMegaman; 
	D3DXVECTOR2* positionCamera;
	int nStage;
	MGMObject** allObjects;
	MGMStage** stages;
	bool isChangeStage;
	Door**doors;
	/*Đọc object và tạo sprite cho object*/
	void readObjects(char* objectsPath);

	void readStage(char* stagePath);
	void readStageSaved(char * stageSavedPath);
	void updateStage();
	void updateStageSaved();
	void update();
	void draw();

	MGMMap(BossMap bm,char* objectsPath,char* tileSheetPath,char* quadTreePath,char* matrixPath,char* stagePath, char* stageSavedPath);
	~MGMMap();
};

