#include "MGMMap.h"
#include"OctopusBattery.h"
#include"PicketMan.h"
#include"MGMSpriteManager.h"
#include"Collision.h"
#include"BigEye.h"
#include"Megaman.h"
#include"stairs.h"
#include "Blader.h"
#include"Beak.h"
#include"MGMGameTime.h"
#include"Flea.h"
#include "FlyingShell.h"
#include"ScrewBomber.h"
#include"SuperCutter.h"
#include"CutMan.h"
#include"CutmanBullet.h"
#include "MGMItem.h"
#include "LifeEnergyBig.h"
#include "Met.h"
#include"BoardBar.h"
#include "Room.h"
#include "BossGutsman.h"
#include "BigRock.h"
#include "GreenBar.h"
#include"StoneDead.h"
#include"Room.h"
#include"MGMAudioManager.h"
#include "CutmanRoom.h"
extern void ignoreLineIfstream(ifstream& fs, int lineCount);

void MGMMap::readObjects(char* objectsPath)
{
	ifstream fs(objectsPath);

	fs >> nObject; //Tổng số object

	allObjects = new MGMObject*[nObject];

	int id, x, y, width, height;
	MGMObject* obj = 0;
	//add
	for (int i = 0; i < nObject; i++)
	{
		fs >> id >> x >> y >> width >> height;
		y = nRow * 16 - y; // Chuyển tọa độ y hướng lên (tọa độ trong map)
		switch (id % 100)
		{
		case SPR_STONE_DIE:
			obj = new StoneDead();
			break;
		case SPR_GROUND:
			obj = new MGMObject();
			break;
			//@Tu-Add
		case SPR_OCTOPUSBATTERY:
			obj = new OctopusBattery();
			break;
		case SPR_PICKETMAN:
			obj = new PicketMan();
			break;
		case SPR_BIGEYE:
			obj = new BigEye();
			break;
		case SPR_STAIRS:
			obj = new stairs();
			break;
			//@Tu-Add
		case SPR_BLADER:
			obj = new Blader();
			break;
		case SPR_BEAK: //@Dung - Add
			obj = new Beak();
			break;
		case SPR_ROOM:
			/*obj = new Room();*/
			obj = Room::getInstance();
			break;
		case SPR_BOSS_GUTSMAN:
			obj = BossGutsman::getInstance();
			break;
		case SPR_BIGROCK:
			obj = new BigRock();
			break;
		case SPR_GREENBAR:
			obj = new GreenBar();
			break;
		case SPR_FLEA:
			obj = new Flea();
			break;
		case SPR_MET:
			obj = new Met();
			break;
			//@Tu-Add
		case SPR_FLYING_SHELL:
			obj = new FlyingShell();
			break;
		case SPR_SCREWBOMBER:
			obj = new ScrewBomber();
			break;
		case SPR_SUPER_CUTTER:
			obj = new SuperCutter();
			break;
		case SPR_CUTMAN:
			obj = CutMan::getInstance();
			break;
		case SPR_CUTMAN_ROOM:
			obj = new CutmanRoom();
			break;
		case SPR_ITEM_LIFE_ENERGY_BIG:
			obj = new LifeEnergyBig(0);
		default:
			break;
		}

		obj->id = id;

		allObjects[i] = obj;

		obj->init(x, y, width, height); //Khoi tao doi tuong

		if (id >= 0)
		{
			obj->sprite = MGMSpriteManager::getInstance()->sprites[id % 100]; //Lấy sprite từ SpriteManager
			MGMMovableObject* mov = (MGMMovableObject*)obj;
			fs >> mov->spaceMove.x >> mov->spaceMove.y >> mov->spaceMove.width >> mov->spaceMove.height;
			mov->spaceMove.y = nRow * 16 - mov->spaceMove.y; // Chuyển tọa độ y hướng lên (tọa độ trong map)

		}

		//doors[2]=new Door
	}
	doors = new Door*[2];
	doors[0] = new Door(2272, 1344, 32, 64);
	doors[0]->id = -3;
	doors[1] = new Door(3071, 1344, 32, 64);
	doors[1]->id = -3;
	if (bossMap == GutsMap)
	{
		doors[0]->x = 2784;
		doors[0]->y = 144;
		doors[1]->x = 3569;
		doors[1]->y = 144;
	}
}

void MGMMap::readStage(char * stagePath)
{
	ifstream fs(stagePath);
	fs >> nStage;
	stages = new MGMStage*[nStage];

	for (int i = 0; i < nStage; i++)
	{
		stages[i] = new MGMStage(fs);
		stages[i]->index = i;
		/*if (MGMStage::checkMegamanInStage(Megaman::getInstance(), stages[i]))
			MGMStage::curStage = stages[i];*/
	}
	//MGMStage::curStage = stages[0];

}
void MGMMap::readStageSaved(char * stageSavedPath)
{
	int nStageSaved;
	ifstream fs(stageSavedPath);
	fs >> nStageSaved;
	positionMegaman = new D3DXVECTOR2[nStageSaved];
	positionCamera = new D3DXVECTOR2[nStageSaved];

	for (int i = 0; i < nStageSaved; i++)
	{
		fs >> positionMegaman[i].x >> positionMegaman[i].y >> positionCamera[i].x >> positionCamera[i].y;
		/*if (MGMStage::checkMegamanInStage(Megaman::getInstance(), stages[i]))
		MGMStage::curStage = stages[i];*/
	}
	fs.close();
}

void MGMMap::updateStage()
{


	Megaman * mgm = Megaman::getInstance();
	MGMStage * curstage = MGMStage::curStage;
	if (mgm->getLeft() < curstage->getLeft() && mgm->getLeft() - mgm->dx >= curstage->getLeft())
		mgm->x = curstage->getLeft();

	if (mgm->getRight() > curstage->getRight() && mgm->getRight() - mgm->dx <= curstage->getRight())
		mgm->x = curstage->getRight() - mgm->width + 1;


	if ((mgm->isOnStairs&&mgm->getYCenter() > MGMStage::curStage->getTop()) || mgm->getYCenter() < MGMStage::curStage->getBottom())
	{
		isChangeStage = false;
		isUpdate = false;
		for (int i = 0; i < nStage; i++)
		{
			if (MGMStage::curStage->index == i) continue;
			if (MGMStage::checkMegamanInStage(Megaman::getInstance(), stages[i]))
			{
				MGMStage::curStage = stages[i];
				isChangeStage = true;
			}
		}
	}

	for (int i = 0; i < 2; i++)
	{

		if (Collision::AABBCheck(mgm, doors[i]))
		{
			if (mgm->objectDirection == RIGHT&&mgm->getRight() <= doors[i]->x)
			{
				isUpdate = false;
				Megaman::getInstance()->dx = 0;
				if (mgm->IntersectDoor < 0)
				{
					mgm->IntersectDoor = i;
					MGMStage::curStage = stages[MGMStage::curStage->index + mgm->objectDirection];
				}
			}
			else
			{
				mgm->x -= mgm->dx;
			}
		}
	}
	if (!isUpdate)
	{

		if (mgm->isOnStairs &&mgm->getYCenter() > MGMStage::curStage->getTop())
		{
			mgm->y += 0.5f;
			mgm->pauseAnimation = false;
			mgm->updateFrameAnimation();
			MGMCamera::getInstance()->dy = 4;

		}

		if (mgm->getYCenter() < MGMStage::curStage->getBottom())
		{
			mgm->y -= 0.5f;
			mgm->pauseAnimation = false;
			mgm->updateFrameAnimation();
			MGMCamera::getInstance()->dy = -4;

		}

		if (mgm->IntersectDoor >= 0)
		{
			if (!doors[mgm->IntersectDoor]->isOpened)
			{
				doors[mgm->IntersectDoor]->Open();
			}
			if (MGMCamera::getInstance()->x >= MGMStage::curStage->x&&MGMCamera::getInstance()->getRight() <= MGMStage::curStage->getRight())
			{
				//isUpdate = true;
				//MGMCamera::getInstance()->dx = 0;
				//doors[mgm->IntersectDoor]->pauseAnimation = false;
				doors[mgm->IntersectDoor]->isOpened = true;
				if (doors[mgm->IntersectDoor]->curFrame == 4)
				{
					doors[mgm->IntersectDoor]->curFrame = 0;
				}
				doors[mgm->IntersectDoor]->Close();
				if (doors[mgm->IntersectDoor]->isClosed)
				{
					isUpdate = true;
					mgm->IntersectDoor = -1;
				}

			}
		}
	}
	if (mgm->IntersectDoor < 0 && MGMStage::curStage->getBottom() <= MGMCamera::getInstance()->getBottom() && MGMCamera::getInstance()->y <= MGMStage::curStage->getTop())
	{
		if (isChangeStage) MGMCamera::getInstance()->dy = 0;
		isUpdate = true;
	}

	updateStageSaved();

}

void MGMMap::updateStageSaved()
{
	bool keyNumberPress = false;
	if (KEY::getInstance()->isOnePress)
	{
		MGMCamera::getInstance()->x = positionCamera[0].x;
		MGMCamera::getInstance()->y = positionCamera[0].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[0].x;
		Megaman::getInstance()->y = positionMegaman[0].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}

	if (KEY::getInstance()->isTwoPress)
	{
		MGMCamera::getInstance()->x = positionCamera[1].x;
		MGMCamera::getInstance()->y = positionCamera[1].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[1].x;
		Megaman::getInstance()->y = positionMegaman[1].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}
	if (KEY::getInstance()->isThreePress)
	{
		MGMCamera::getInstance()->x = positionCamera[2].x;
		MGMCamera::getInstance()->y = positionCamera[2].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[2].x;
		Megaman::getInstance()->y = positionMegaman[2].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}
	if (KEY::getInstance()->isFourPress)
	{
		MGMCamera::getInstance()->x = positionCamera[3].x;
		MGMCamera::getInstance()->y = positionCamera[3].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[3].x;
		Megaman::getInstance()->y = positionMegaman[3].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}
	if (KEY::getInstance()->isFivePress)
	{
		MGMCamera::getInstance()->x = positionCamera[4].x;
		MGMCamera::getInstance()->y = positionCamera[4].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[4].x;
		Megaman::getInstance()->y = positionMegaman[4].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}
	if (KEY::getInstance()->isSixPress)
	{
		MGMCamera::getInstance()->x = positionCamera[5].x;
		MGMCamera::getInstance()->y = positionCamera[5].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[5].x;
		Megaman::getInstance()->y = positionMegaman[5].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}
	if (KEY::getInstance()->isSevenPress)
	{

		MGMCamera::getInstance()->x = positionCamera[6].x;
		MGMCamera::getInstance()->y = positionCamera[6].y;
		MGMCamera::getInstance()->dx = MGMCamera::getInstance()->dy = 0;
		Megaman::getInstance()->x = positionMegaman[6].x;
		Megaman::getInstance()->y = positionMegaman[6].y;
		Megaman::getInstance()->isKill = false;
		keyNumberPress = true;
	}
	if (keyNumberPress)
	{
		for (int i = 0; i < nStage; i++)
		{
			if (MGMStage::checkMegamanInStage(Megaman::getInstance(), stages[i]))
				MGMStage::curStage = stages[i];
		}
	}
}

void MGMMap::update()
{


	quadTree->update();


	int nObjectsCam = MGMCamera::getInstance()->objects.allObjects.size();
	for (int i = 0; i < nObjectsCam; i++)
	{
		MGMCamera::getInstance()->objects.allObjects[i]->update();
	}

	List<MGMObject*>& enemyObjects = MGMCamera::getInstance()->objects.enemyObjects;
	List<MGMObject*>& groundObjects = MGMCamera::getInstance()->objects.groundObjects;
	List<MGMObject*>& stairObjects = MGMCamera::getInstance()->objects.stairObjects;
	List<MGMObject*>& itemObjects = MGMCamera::getInstance()->objects.itemObjects;
	List<MGMObject*>& bigRockObjects = MGMCamera::getInstance()->objects.bigRockObjects; //Dung

	int nGround = groundObjects.size();

	for (int iGround = 0; iGround < nGround; iGround++)
	{
		if (MGMStage::checkObjectInStage(groundObjects[iGround], MGMStage::curStage))
			Collision::checkCollision(Megaman::getInstance(), groundObjects[iGround]);
		if (CutmanBullet::bullet != NULL) {
			Collision::checkCollision(groundObjects[iGround], CutmanBullet::getBullet());
		}
		for (int i = 0; i < itemObjects.size(); i++) {
			MGMObject* item = itemObjects.at(i);
			Collision::checkCollision(item, groundObjects[iGround]);
		}
	}
	for (int i = 0; i < itemObjects.size(); i++) {
		MGMObject* item = itemObjects.at(i);
		Collision::checkCollision(Megaman::getInstance(), item);
	}

	// Dung: Xét va chạm với viên gạch loại lớn:
	int nBigRock = bigRockObjects.size();

	for (int iBigRock = 0; iBigRock < nBigRock; iBigRock++)
	{
		Collision::checkCollision(Megaman::getInstance(), bigRockObjects[iBigRock]);
	}
	//------
	int nStair = stairObjects.size();
	stairs* s;
	for (int i = 0; i < nStair; i++)
	{
		s = (stairs*)stairObjects[i];
		s->climbStairs();

	}

	/*int nEnemy = enemyObjects.size();*/


	for (int iEnemy = 0; iEnemy < enemyObjects.size(); iEnemy++)
	{

		MGMObject*enemy = enemyObjects.at(iEnemy);
		//if (enemy->isKill){
		//	MGMCamera::getInstance()->objects.removeObject(enemy);
		//	/*delete enemy;*/
		//	iEnemy--;
		//}
		//else{
		Collision::checkCollision(Megaman::getInstance(), enemy);
		for (int iGround = 0; iGround < nGround; iGround++)
		{
			Collision::checkCollision(enemy, groundObjects[iGround]);
		}

		// Dung: Check giữa enemy và các viên gạch lớn:
		for (int iBigRock = 0; iBigRock < nBigRock; iBigRock++)
		{
			Collision::checkCollision(enemy, bigRockObjects[iBigRock]);
		}
		// Dung: Check giữa CutManBullet và Cutman:
		Collision::checkCollision(enemy, CutmanBullet::getBullet());
		/*}*/
	}

	int nDoor = 2;
	for (int i = 0; i < nDoor; i++) {
		Collision::checkCollision(CutMan::getInstance(), this->doors[i]);

	}
	//test
	//for (List<MGMItem*>::Node*p = MGMItem::getListItem()->pHead; p; p = p->pNext){
	//	MGMItem* item = p->m_value;
	//	Collision::checkCollision(Megaman::getInstance(), item);
	//}
	nObjectsCam = MGMCamera::getInstance()->objects.allObjects.size();
	for (int i = 0; i < nObjectsCam; i++)
	{
		MGMCamera::getInstance()->objects.allObjects[i]->coordinateUpdate();
	}
}

void MGMMap::draw()
{

	MGMTileMap::draw();
	if (!BoardBar::getInstance()->isPause) {

		int nObjectsCam = MGMCamera::getInstance()->objects.allObjects.size();
		for (int i = 0; i < nObjectsCam; i++)
		{
			MGMCamera::getInstance()->objects.allObjects[i]->render();
		}
		for (int i = 0; i < 2; i++)
		{
			doors[i]->render();
		}
	}

}

MGMMap::MGMMap(BossMap bm, char * objectsPath, char * tileSheetPath, char * quadTreePath, char * matrixPath, char* stagePath, char* stageSavedPath) :
	MGMTileMap(matrixPath, tileSheetPath) //Doc tile map
{
	bossMap = bm;
	readObjects(objectsPath);
	quadTree = new QuadTree(quadTreePath, allObjects, nRow * 16);
	readStage(stagePath);
	readStageSaved(stageSavedPath);
	isUpdate = true;

}

MGMMap::~MGMMap()
{
	for (int i = 0; i < nStage; i++)
	{
		if (stages[i] != NULL)
			delete stages[i];

	}
	if (stages != NULL) delete[] stages;
	for (int i = 0; i < nObject; i++)
	{
		if (allObjects[i] != NULL)
			delete allObjects[i];
	}
	if (allObjects != NULL) delete[] allObjects;
	for (int i = 0; i < 2; i++)
	{
		if (doors[i] != NULL)
			delete doors[i];
	}
	if (doors != NULL) delete[]doors;
}
