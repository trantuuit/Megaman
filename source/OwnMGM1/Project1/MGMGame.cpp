#include "MGMGame.h"
#include"Keyboard.h"
#include"MGMDirectXTool.h"
#include"KEY.h"
#include"MegamanBullet.h"
#include"BeakBullet.h"
MGMGame::MGMGame()
{
}
MGMGame* MGMGame::instance = 0;
MGMGame *MGMGame::getInstance()
{
	if (instance == 0) instance = new MGMGame();
	return instance;
}

MGMGame::~MGMGame()
{

}
void MGMGame::init()
{

	Megaman::getInstance()->x = 22;
	Megaman::getInstance()->y = 111;

	MGMCamera::getInstance()->init(0, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	/*Megaman::getInstance()->x = 950;
	Megaman::getInstance()->y = 1100;
	MGMCamera::getInstance()->init(768, 1192, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	//tọa độ gần screwbomber
	Megaman::getInstance()->x = 2250;
	Megaman::getInstance()->y = 1350;

	MGMCamera::getInstance()->init(2040, 1432, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	MGMCamera::getInstance()->dx = 0;
	MGMCamera::getInstance()->dy = 0;
	//Khoi tao map
	map = new MGMMap("Data\\TileMap\\objects.txt", "Data\\TileMap\\tileSheet.png", "Data\\TileMap\\quadtree.txt", "Data\\TileMap\\matrix.txt",
		"Data\\TileMap\\stage.txt");
}
void MGMGame::render()
{
	map->draw();
	Megaman::getInstance()->render();

	for (List<MegamanBullet*>::Node* p = MegamanBullet::getBullets()->pHead; p; p = p->pNext)
	{
		MegamanBullet* bullet = p->m_value;
		bullet->render();
	}

	for (List<BeakBullet*>::Node *p = BeakBullet::getBullets()->pHead; p; p = p->pNext)
	{
		BeakBullet *_bullet = p->m_value;
		_bullet->render();
	}
}
void MGMGame::update(DWORD timesleep)
{

	if (map->isUpdate)
	{
		Megaman::getInstance()->update(); // Cap nhat van toc cua MGM
		map->update();
	}
	MGMCamera::getInstance()->update();
	if (map->isUpdate)
	{
		//Megaman::getInstance()->updateFrameAnimation();
		Megaman::getInstance()->updateLocation(); // Cap nhat toa do cua MGM
	}
	map->updateStage();

	for (List<MegamanBullet*>::Node* p = MegamanBullet::getBullets()->pHead; p; p = p->pNext)
	{
		MegamanBullet* bullet = p->m_value;
		bullet->updateLocation();
	}

	for (int i = 0; i < MegamanBullet::getBullets()->Count; i++)
	{
		MegamanBullet*bullet = MegamanBullet::getBullets()->at(i);
		if (!Collision::AABBCheck(bullet , MGMCamera::getInstance()))
		{
			MegamanBullet::getBullets()->_Remove(bullet);
			delete bullet;
			i--;
		}
	}


	//------------------------------------------------------------------------------------------------------------------
	// Update tọa độ các viên đạn:
	for (List<BeakBullet*>::Node *p = BeakBullet::getBullets()->pHead; p; p = p->pNext)
	{
		BeakBullet *_bullet = p->m_value;
		_bullet->updateLocation();
	}

	// Xóa các viên đạn không nằm trong Camera:
	for (int i = 0; i < BeakBullet::getBullets()->Count; i++)
	{
		BeakBullet* bullet = BeakBullet::getBullets()->at(i);
		if (!Collision::AABBCheck(bullet, MGMCamera::getInstance()))
		{
			BeakBullet::getBullets()->_Remove(bullet);
			delete bullet;
			i--;
		}
	}
}