#include "MGMTileMap.h"



MGMTileMap::MGMTileMap(const char* matrixPath, const char* tileSheetPath)
{
	fstream fs(matrixPath);

	fs >> nRow; // So hang ma tran tile
	fs >> nCol; // So cot ma tran tile
	fs >> tilesColCount; // so cot cua tileSheet


	matrix = new int*[nRow]; //khoi tao gia tri ban dau cho matrix

	//doc ma tran tile-map
	for (int i = 0; i < nRow; i++)
	{
		matrix[i] = new int[nCol];
		for (int j = 0; j < nCol; j++)
		{
			fs >> matrix[i][j];
		}
	}

	tileSheet.Init(tileSheetPath, D3DCOLOR_XRGB(123, 123, 123)); //Tao texture tu tileSheet
}


void MGMTileMap::drawTile(int rowIndex, int colIndex)
{
	auto camera = MGMCamera::getInstance();
	int indexInTileSheet = matrix[rowIndex][colIndex];

	float xTileRender, yTileRender;

	//camera->Transform(colIndex * 16, (nRow - rowIndex) * 16, xTileRender, yTileRender);

	xTileRender = colIndex * 16 - camera->x;
	yTileRender = rowIndex * 16 - (nRow * 16 - camera->y);


	RECT rectIndex;
	int xRect = (indexInTileSheet % tilesColCount) * 16;
	int yRect = (indexInTileSheet / tilesColCount) * 16;
	SetRect(&rectIndex, xRect , 
		yRect, xRect + 16, yRect + 16);

	tileSheet.RenderTexture(xTileRender, yTileRender, &rectIndex);

}

void MGMTileMap::drawTiles(int rowBegin, int rowEnd, int colBegin, int colEnd)
{
	auto camera = MGMCamera::getInstance();

	if (colBegin>colEnd ||rowBegin>rowEnd)
		return;
	if (colBegin < 0)
	{
		colBegin = 0;
	}
	if (rowBegin<0)
	{
		rowBegin=0;
	}
	if (colEnd > nCol - 1)
	{
		colEnd = nCol - 1;
	}
	if (rowEnd > nRow - 1)
	{
		rowEnd = nRow - 1;
	}
	for (int rowIndex = rowBegin; rowIndex <= rowEnd; rowIndex++)
	{
		for (int colIndex = colBegin; colIndex <= colEnd; colIndex++)
		{
			drawTile(rowIndex, colIndex);
		}
	}
}

void MGMTileMap::draw()
{
	auto camera = MGMCamera::getInstance();

	int cBegin, cEnd, rBegin, rEnd;

	cBegin = camera->getLeft() / 16;
	cEnd = camera->getRight() / 16;

	rBegin = (nRow*16 - camera->getTop()) / 16;
	rEnd = (nRow * 16 - camera->getBottom()) / 16;

	drawTiles(rBegin, rEnd, cBegin, cEnd);
}

MGMTileMap::~MGMTileMap()
{
	for (int i = 0; i < nRow; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}
