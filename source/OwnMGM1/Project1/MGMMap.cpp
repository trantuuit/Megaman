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
		case SPR_FLEA:
			obj = new Flea();
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
		default:
			obj = new MGMObject();
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
		doors = new Door*[3];
		doors[0] = new Door(2272, 1344, 32, 64);
		doors[1] = new Door(3072, 1344, 32, 64);
		//doors[2]=new Door
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
		if (MGMStage::checkMegamanInStage(Megaman::getInstance(), stages[i]))
			MGMStage::curStage = stages[i];
	}
	//MGMStage::curStage = stages[0];

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

	/*if (Collision::AABBCheck(mgm, doors[0]))
	{
		isUpdate = false;
		if (mgm->IntersectDoor != 0)
		{
			mgm->IntersectDoor = 0;
			MGMStage::curStage = stages[MGMStage::curStage->index + mgm->objectDirection];
		}
	}*/
	for (int i = 0; i < 2; i++)
	{

		if (Collision::AABBCheck(mgm, doors[i]))
		{
			if (mgm->objectDirection == RIGHT)
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


	int nGround = groundObjects.size();

	for (int iGround = 0; iGround < nGround; iGround++)
	{
		if (MGMStage::checkObjectInStage(groundObjects[iGround], MGMStage::curStage))
			Collision::checkCollision(Megaman::getInstance(), groundObjects[iGround]);
	}

	int nStair = stairObjects.size();
	stairs* s;
	for (int i = 0; i < nStair; i++)
	{
		s = (stairs*)stairObjects[i];
		s->climbStairs();

	}
	int nEnemy = enemyObjects.size();

	for (int iEnemy = 0; iEnemy < nEnemy; iEnemy++)
	{
		auto enemy = enemyObjects[iEnemy];
		Collision::checkCollision(Megaman::getInstance(), enemy);
		for (int iGround = 0; iGround < nGround; iGround++)
		{
			Collision::checkCollision(enemy, groundObjects[iGround]);
		}
	}


	for (int i = 0; i < nObjectsCam; i++)
	{
		MGMCamera::getInstance()->objects.allObjects[i]->updateLocation();
	}


}

void MGMMap::draw()
{
	MGMTileMap::draw();
	int nObjectsCam = MGMCamera::getInstance()->objects.allObjects.size();
	for (int i = 0; i < 2; i++)
	{
		doors[i]->render();
	}
	for (int i = 0; i < nObjectsCam; i++)
	{
		MGMCamera::getInstance()->objects.allObjects[i]->render();
	}
}

MGMMap::MGMMap(char * objectsPath, char * tileSheetPath, char * quadTreePath, char * matrixPath, char* stagePath) :
	MGMTileMap(matrixPath, tileSheetPath) //Doc tile map
{
	readObjects(objectsPath);
	quadTree = new QuadTree(quadTreePath, allObjects, nRow * 16);
	readStage(stagePath);
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
