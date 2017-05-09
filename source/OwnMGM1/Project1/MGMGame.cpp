#include "MGMGame.h"
#include"Keyboard.h"
#include"MGMDirectXTool.h"
#include"KEY.h"
#include"MegamanBullet.h"
#include"BeakBullet.h"
#include"SuperCutter.h"
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

	//----------------------------------------------------SUPER CUTTER-------------------------------------------------------------

	// Xét tọa độ của Megaman so với ngôi nhà (nhằm new SuperCuterr())
	if (SuperCutter::isAppear())
	{
		int distance;
		if (SuperCutter::location == LOCATION_1)
			distance = Megaman::getInstance()->getXCenter() - 912;  // Tâm nơi SuperCutter được sinh ra có tọa độ là 913
		else
			distance = Megaman::getInstance()->getXCenter() - 1424; // Tâm nơi SuperCutter được sinh ra có tọa độ là 1424
		if (SuperCutter::timeDelay.isTerminated())
		{
			SuperCutter *supperCutter = new SuperCutter();
			if (SuperCutter::location == LOCATION_1)
			{
				supperCutter->x = 905;
				supperCutter->y = 1040;
			}
			else
			{
				supperCutter->x = 1416;
				supperCutter->y = 2000;
			}
			SuperCutter::timeDelay.start(300);
			supperCutter->vx = (float)distance / 232;  // Xác định 1 hằng số để tính ra vận tốc phù hợp
			supperCutter->objectDirection = (supperCutter->vx < 0) ? LEFT : RIGHT;

		}
		SuperCutter::timeDelay.update();
	}
	// Cập nhật tọa độ các SuperCutter:
	for (int i = 0; i < SuperCutter::getSuperCutters()->Count; i++)
	{
		SuperCutter *s = SuperCutter::getSuperCutters()->at(i);
		s->update();
		s->updateLocation();
	}

	// Xóa các Super Cutter không nằm trong Camera:
	for (int i = 0; i < SuperCutter::getSuperCutters()->Count; i++)
	{
		SuperCutter *s = SuperCutter::getSuperCutters()->at(i);
		if (!Collision::AABBCheck(s, MGMCamera::getInstance()))
		{
			SuperCutter::getSuperCutters()->_Remove(s);
			delete s;
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