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
#include"ScoreBar.h"
#include"BoardBar.h"
#include"PKMWeapon.h"
#include "SmallRock.h"
#include"DieEffect.h"
#include"EffectCreateItem.h"
#include"PKMWeapon.h"
#include"MGMAudioManager.h"
#include"BossGutsman.h"
#include"CutMan.h"
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
	/*Megaman::getInstance()->x = 22;
	Megaman::getInstance()->y = 111;
	MGMCamera::getInstance()->init(0, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

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
	//Megaman::getInstance()->x = 830;
	//Megaman::getInstance()->y = 1100;
	//MGMCamera::getInstance()->init(800, 1200, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	// Test SuperCutter vị trí 2
	/*Megaman::getInstance()->x = 1322;
	Megaman::getInstance()->y = 1975;
	MGMCamera::getInstance()->init(1300, 2100, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	// Test BigEye
	/*Megaman::getInstance()->x = 1900;
	Megaman::getInstance()->y = 1335;
	MGMCamera::getInstance()->init(1800, 1435, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	//stage dau voi cutman
	//Megaman::getInstance()->x = 3120;
	//Megaman::getInstance()->y = 1432;
	//MGMCamera::getInstance()->init(3088, 1432, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	// Vị trí trước thanh trượt màu xanh map Gutsman:
	//Megaman::getInstance()->x = 400;
	//Megaman::getInstance()->y = 1170;
	//MGMCamera::getInstance()->init(350, 1176, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);

	//// Vị trí BigEye map Gutsman
	/*Megaman::getInstance()->x = 2372;
	Megaman::getInstance()->y = 135;
	MGMCamera::getInstance()->init(2304, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	//// Vị trí cuối map GutsMan
	/*Megaman::getInstance()->x = 3600;
	Megaman::getInstance()->y = 140;
	MGMCamera::getInstance()->init(3585, 232, BACKBUFFER_WIDTH, BACKBUFFER_HEIGHT);*/

	isStart = true;
	MGMCamera::getInstance()->dx = 0;
	MGMCamera::getInstance()->dy = 0;
	//Khoi tao map
	mapCut = new MGMMap(CutMap, "Data\\MapCut\\objects.txt", "Data\\MapCut\\tileSheet.png", "Data\\MapCut\\quadtree.txt", "Data\\MapCut\\matrix.txt",
		"Data\\MapCut\\stage.txt","Data\\MapCut\\stageSaved.txt");
	mapGut = new MGMMap(GutsMap, "Data\\MapGut\\objects.txt", "Data\\MapGut\\tileSheet.png", "Data\\MapGut\\quadtree.txt", "Data\\MapGut\\matrix.txt",
		"Data\\MapGut\\stage.txt","Data\\MapGut\\stageSaved.txt");

	//Dung test Boss Cutman
	//mapCut = new MGMMap(CutMap, "Data\\Tilemap_CutManRoom\\objects.txt", "Data\\Tilemap_CutManRoom\\tileSheet.png", "Data\\Tilemap_CutManRoom\\quadtree.txt", "Data\\Tilemap_CutManRoom\\matrix.txt",
	//	"Data\\Tilemap_CutManRoom\\stage.txt");

}
void MGMGame::render()
{
	if (!BoardBar::getInstance()->isPause){
		map->draw();
		HPBar::getInstance()->render();
		ScoreBar::getInstance()->render();

		if (!Megaman::getInstance()->isKill){
			Megaman::getInstance()->render();
		}

		for (List<MegamanBullet*>::Node* p = MegamanBullet::getListBullet()->pHead; p; p = p->pNext)
		{
			MegamanBullet* bullet = p->m_value;
			bullet->render();
		}

		for (List<PKMWeapon*>::Node* p = PKMWeapon::getListHammer()->pHead; p; p = p->pNext)
		{
			PKMWeapon* hammer = p->m_value;
			hammer->render();
		}

		//Render affect
		for (List<DieAffect*>::Node *p = DieAffect::getList()->pHead; p; p = p->pNext)
		{
			DieAffect * effect = p->m_value;
			effect->render();
		}
		EffectCreateItem::getInstance()->render();
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

		// Render SmallRocks:
		for (int i = 0; i < SmallRock::getSmallRocks()->Count; i++)
		{
			SmallRock *s = SmallRock::getSmallRocks()->at(i);
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
	else{
		map->draw();
	}
	BoardBar::getInstance()->render();
}
void MGMGame::update(DWORD timesleep)
{
	if (map == mapCut){
		MGMAudioManager::getInstance()->Play(AUDIO_CUTMAN);
		if (Megaman::getInstance()->isKill){
			MGMAudioManager::getInstance()->StopSound(AUDIO_CUTMAN);
		}
		if (CutMan::getInstance()->appearMusic){
			MGMAudioManager::getInstance()->StopSound(AUDIO_CUTMAN);
			MGMAudioManager::getInstance()->Play(AUDIO_BOSS_BATTLE);
		}
		if (CutMan::getInstance()->isKill){
			MGMAudioManager::getInstance()->StopSound(AUDIO_BOSS_BATTLE);
		}
	}
	else{
		MGMAudioManager::getInstance()->Play(AUDIO_GUTMAN);
		if (Megaman::getInstance()->isKill){
			MGMAudioManager::getInstance()->StopSound(AUDIO_GUTMAN);
		}
		if (BossGutsman::getInstance()->appearMusic){
			MGMAudioManager::getInstance()->StopSound(AUDIO_GUTMAN);
			MGMAudioManager::getInstance()->Play(AUDIO_BOSS_BATTLE);
		}
		if (BossGutsman::getInstance()->isKill){
			MGMAudioManager::getInstance()->StopSound(AUDIO_BOSS_BATTLE);
		}
	}
	BoardBar::getInstance()->update();
	if (!BoardBar::getInstance()->isPause){
		if (map->isUpdate)
		{
			HPBar::getInstance()->update();
			ScoreBar::getInstance()->update();
			//Megaman ko chet thi update
			if (!Megaman::getInstance()->isKill){
				Megaman::getInstance()->update();
			}
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
		/*int nEnemy = enemyObjects.size();*/
		//Cap nhat hieu ung
		for (List<DieAffect*>::Node *p = DieAffect::getList()->pHead; p; p = p->pNext)
		{
			DieAffect * effect = p->m_value;
			effect->updateFrameAnimation();
			effect->coordinateUpdate();
		}
		//Xoa hieu ung ra khoi camera
		for (int i = 0; i < DieAffect::getList()->Count; i++)
		{
			DieAffect* effect = DieAffect::getList()->at(i);
			if (!Collision::AABBCheck(effect, MGMCamera::getInstance()))
			{
				DieAffect::getList()->_Remove(effect);
				delete effect;
				i--;
			}
		}
		EffectCreateItem::getInstance()->update();
		//Cap nhat vi tri cua vien dan megaman
		for (List<MegamanBullet*>::Node* p = MegamanBullet::getListBullet()->pHead; p; p = p->pNext)
		{
			MegamanBullet* bullet = p->m_value;
			bullet->update();
			for (int iEnemy = 0; iEnemy < enemyObjects.size(); iEnemy++)
			{
				auto enemy = enemyObjects[iEnemy];
				Collision::checkCollision(bullet, enemy);

			}
			Collision::checkCollision(bullet, Megaman::getInstance());
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
		if (SuperCutter::isAppear() && map == mapCut)
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
			Collision::checkCollision(Megaman::getInstance(), s);
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
			if (!Collision::AABBCheck(bullet, MGMCamera::getInstance()) || bullet->isKill)
			{
				EnemyBullet::getListBullet()->_Remove(bullet);
				delete bullet;
				i--;
			}
		}


		//---------------------------------------SMALL ROCK---------------------------------------------------------------------------
		// Update tọa độ các small rocks:
		for (List<SmallRock*>::Node *p = SmallRock::getSmallRocks()->pHead; p; p = p->pNext)
		{
			SmallRock *_smallRock = p->m_value;
			Collision::checkCollision(Megaman::getInstance(), _smallRock);
			_smallRock->coordinateUpdate();
		}

		// Ra khỏi Camera thì xóa:
		for (int i = 0; i < SmallRock::getSmallRocks()->Count; i++)
		{
			SmallRock* smallRock = SmallRock::getSmallRocks()->at(i);
			if (!Collision::AABBCheck(smallRock, MGMCamera::getInstance()))
			{
				SmallRock::getSmallRocks()->_Remove(smallRock);
				delete smallRock;
				i--;
			}
		}
		//Cutman bullet
		if (CutmanBullet::bullet != NULL){
			CutmanBullet::getBullet()->update();
			Collision::checkCollision(CutmanBullet::bullet, Megaman::getInstance());
			CutmanBullet::getBullet()->coordinateUpdate();
		}

	}

	//Pitketman hammer
	for (List<PKMWeapon*>::Node* p = PKMWeapon::getListHammer()->pHead; p; p = p->pNext)
	{
		PKMWeapon* bullet = p->m_value;

		bullet->deltaUpdate();
		if (Collision::AABBCheck(bullet, Megaman::getInstance()))
		{
			//bullet->onIntersectRect(Megaman::getInstance());
			Megaman::getInstance()->onIntersectRect(bullet);
		}
		bullet->updateFrameAnimation();
		bullet->coordinateUpdate();
	}
	//Xoa vien dan cua pkm
	for (int i = 0; i < PKMWeapon::getListHammer()->Count; i++)
	{
		PKMWeapon*bullet = PKMWeapon::getListHammer()->at(i);
		if (!Collision::AABBCheck(bullet, MGMCamera::getInstance()) || bullet->isKill)
		{
			PKMWeapon::getListHammer()->_Remove(bullet);
			delete bullet;
			i--;

		}
	}
}

