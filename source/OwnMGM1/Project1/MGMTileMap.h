#pragma once
#include <fstream>
#include"MGMTexture.h"
#include"MGMRectangle.h"
#include"MGMCamera.h"
using namespace std;
class MGMTileMap
{
public:
	MGMTexture tileSheet;
	int** matrix;
	int nRow;
	int nCol;
	int tilesColCount;

	/* 
	-Doc ma tran tile
	-Tao texture tu tileSheet
	*/
	MGMTileMap(const char* matrixPath, const char* tileSheetPath);


	//ve 1 cai tile len man hinh
	void drawTile(int rowIndex, int colIndex);

	//ve nhieu tile tu 
	void drawTiles(int rowBegin, int rowEnd, int colBegin, int colEnd);

	// ve 1 loat tile theo camera
	virtual void draw();

	~MGMTileMap();
};

