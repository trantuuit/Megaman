#include "MGMCamera.h"
#include"Megaman.h"
#include"MGMStage.h"

MGMCamera* MGMCamera::instance = 0;
MGMCamera* MGMCamera::getInstance(){
	if (instance == 0){
		instance = new MGMCamera();
	}
	return instance;
}
MGMCamera::MGMCamera()
{

}


MGMCamera::~MGMCamera()
{
}

void MGMCamera::Transform(float x, float y, float& xRender, float& yRender)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -this->x;
	matrix._42 = this->y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);

	xRender = MatrixResult.x;
	yRender = MatrixResult.y;

}

void MGMCamera::update()
{
	dx = 0;
	int mgmX = Megaman::getInstance()->x;
	int mgmDx = Megaman::getInstance()->dx;
	
	if( (mgmDx<0 && Megaman::getInstance()->getXCenter() + mgmDx< getXCenter())
		||
		(mgmDx>0 && Megaman::getInstance()->getXCenter() + mgmDx> getXCenter())
		)
	dx = Megaman::getInstance()->dx;

	if (x + dx < MGMStage::curStage->getLeft())
	{
		x = MGMStage::curStage->getLeft();
		dx = 0;
	}

	if (getRight() + dx > MGMStage::curStage->getRight())
	{
		x = MGMStage::curStage->getRight() - width;
		dx = 0;
	}

	/*dy = 0;
	if (y + dy > MGMStage::curStage->getTop())
	{
		y = MGMStage::curStage->getTop();
		dy = 0;
	}
	if (getBottom() + dy < MGMStage::curStage->getBottom())
	{
		y = MGMStage::curStage->getBottom()+height;
		dy = 0;
	}*/
	//dy = Megaman::getInstance()->dy;
	x += dx;
	y += dy;
}
