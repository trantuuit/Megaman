#include "MGMGame.h"
#include"Keyboard.h"
#include"MGMDirectXTool.h"
#include"KEY.h"
#include"MegamanBullet.h"
#include"EnemyBullet.h"
#include"SuperCutter.h"
#include "CutmanBullet.h"
#include"MGMItem.h"
#include"HPBar.h"
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
	// Mặc định map Cutman:
	Megaman::getInstance()->x = 22;
	Megaman::getInstance()->y = 111;
	MGMCamera::getInstance()->init(0, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	//Megaman::getInstance()->x = 950;
	//Megaman::getInstance()->y = 1100;
	//MGMCamera::getInstance()->init(768, 1192, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	//tọa độ gần BigEye
	/*Megaman::getInstance()->x = 1880;
	Megaman::getInstance()->y = 1400;
	MGMCamera::getInstance()->init(1780, 1460, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	// Vị trí mặc định map GutsMan
	/*Megaman::getInstance()->x = 50;
	Megaman::getInstance()->y = 1150;
	MGMCamera::getInstance()->init(0, 1176, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/


	//// Vị trí 2 map GutsMan
	//Megaman::getInstance()->x = 1230;
	//Megaman::getInstance()->y = 1150;
	//MGMCamera::getInstance()->init(1200, 1176, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	// Vị trí 3 map GutsMan
	/*Megaman::getInstance()->x = 2360;
	Megaman::getInstance()->y = 1090;
	MGMCamera::getInstance()->init(2350, 1176, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	// Test SuperCutter vị trí 1
	/*Megaman::getInstance()->x = 830;
	Megaman::getInstance()->y = 1100;
	MGMCamera::getInstance()->init(800, 1200, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	// Test SuperCutter vị trí 2
	/*Megaman::getInstance()->x = 1322;
	Megaman::getInstance()->y = 1975;
	MGMCamera::getInstance()->init(1300, 2100, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	// Test BigEye
	/*Megaman::getInstance()->x = 1900;
	Megaman::getInstance()->y = 1335;
	MGMCamera::getInstance()->init(1800, 1435, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	//stage dau voi cutman
	/*Megaman::getInstance()->x = 3120;
	Megaman::getInstance()->y = 1432;
	MGMCamera::getInstance()->init(3088, 1432, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	MGMCamera::getInstance()->dx = 0;
	MGMCamera::getInstance()->dy = 0;
	//Khoi tao map
	map = new MGMMap("Data\\TileMap\\objects.txt", "Data\\TileMap\\tileSheet.png", "Data\\TileMap\\quadtree.txt", "Data\\TileMap\\matrix.txt",
		"Data\\TileMap\\stage.txt");
}
void MGMGame::render()
{
	map->draw();
	HPBar::getInstance()->render();
	Megaman::getInstance()->render();

	for (List<MegamanBullet*>::Node* p = MegamanBullet::getListBullet()->pHead; p; p = p->pNext)
	{
		MegamanBullet* bullet = p->m_value;
		bullet->render();
	}

	// Render EnemyBullet:
	for (List<EnemyBullet*>::Node *p = EnemyBullet::getListBullet()->pHead; p; p = p->pNext)
	{
		EnemyBullet *_bullet = p->m_value;
		_bullet->render();
	}

	// Render Super Cutter:
	for (int i = 0; i < SuperCutter::getSuperCutters()->Count; i++)
	{
		SuperCutter *s = SuperCutter::getSuperCutters()->at(i);
		s->render();
	}

	//
	if (CutmanBullet::bullet != NULL){
		CutmanBullet::getBullet()->render();
	}
	//render item
	for (List<MGMItem*>::Node*p = MGMItem::getListItem()->pHead; p; p = p->pNext){
		MGMItem* item = p->m_value;
		item->render();
	}
}
void MGMGame::update(DWORD timesleep)
{

	if (map->isUpdate)
	{
		HPBar::getInstance()->update();
		Megaman::getInstance()->update(); // Cap nhat van toc cua MGM
		map->update();
		//Cap nhat vi tri item
		//Xet va cham voi gach
		for (List<MGMItem*>::Node*p = MGMItem::getListItem()->pHead; p; p = p->pNext){
			MGMItem* item = p->m_value;
			item->update();
		}
	}
	MGMCamera::getInstance()->update();
	if (map->isUpdate)
	{
		//Megaman::getInstance()->updateFrameAnimation();
		Megaman::getInstance()->coordinateUpdate(); // Cap nhat toa do cua MGM
	}
	map->updateStage();

	List<MGMObject*>& enemyObjects = MGMCamera::getInstance()->objects.enemyObjects;
	int nEnemy = enemyObjects.size();


	//Cap nhat vi tri cua vien dan megaman
	for (List<MegamanBullet*>::Node* p = MegamanBullet::getListBullet()->pHead; p; p = p->pNext)
	{
		MegamanBullet* bullet = p->m_value;
		bullet->update();
		for (int iEnemy = 0; iEnemy < nEnemy; iEnemy++)
		{
			auto enemy = enemyObjects[iEnemy];
			Collision::checkCollision(bullet, enemy);
		}
		
		bullet->coordinateUpdate();
	}
	//Xoa vien dan cua megaman
	for (int i = 0; i < MegamanBullet::getListBullet()->Count; i++)
	{
		MegamanBullet*bullet = MegamanBullet::getListBullet()->at(i);
		if (!Collision::AABBCheck(bullet, MGMCamera::getInstance()) || bullet->isKill)
		{
			MegamanBullet::getListBullet()->_Remove(bullet);
			delete bullet;
			i--;
		}
	}

	//Cap nhat vi tri item
	//Xet va cham voi gach, voi megaman
	List<MGMObject*>& groundObjects = MGMCamera::getInstance()->objects.groundObjects;
	for (List<MGMItem*>::Node*p = MGMItem::getListItem()->pHead; p; p = p->pNext){
		MGMItem* item = p->m_value;
		Collision::checkCollision(Megaman::getInstance(), item);
		for (int i = 0; i < groundObjects.size(); i++){
			auto ground = groundObjects[i];
			Collision::checkCollision(item, ground);
		}
		item->coordinateUpdate();
	}
	//Xoa item 
	for (int i = 0; i < MGMItem::getListItem()->Count; i++){
		MGMItem* item = MGMItem::getListItem()->at(i);
		if (!Collision::AABBCheck(item, MGMCamera::getInstance()) || item->isKill){
			MGMItem::getListItem()->_Remove(item);
			delete item;
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
		if (SuperCutter::timeDelay.isFinish())
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
		Collision::checkCollision(Megaman::getInstance(),s );
		/*s->deltaUpdate();
		s->updateFrameAnimation();*/
		s->update();
		s->coordinateUpdate();
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
	for (List<EnemyBullet*>::Node *p = EnemyBullet::getListBullet()->pHead; p; p = p->pNext)
	{

		EnemyBullet *bullet = p->m_value;
		Collision::checkCollision(bullet, Megaman::getInstance());
		bullet->coordinateUpdate();
	}

	// Xóa các viên đạn không nằm trong Camera:
	for (int i = 0; i < EnemyBullet::getListBullet()->Count; i++)
	{
		EnemyBullet* bullet = EnemyBullet::getListBullet()->at(i);
		if (!Collision::AABBCheck(bullet, MGMCamera::getInstance())|| bullet->isKill)
		{
			EnemyBullet::getListBullet()->_Remove(bullet);
			delete bullet;
			i--;
		}
	}

	//Cutman bullet
	if (CutmanBullet::bullet != NULL){
		CutmanBullet::getBullet()->update();
		CutmanBullet::getBullet()->coordinateUpdate();
	}

}