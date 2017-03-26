#include "MGMMap.h"
#include"OctopusBattery.h"
#include"PicketMan.h"
#include"MGMSpriteManager.h"
#include"Collision.h"
#include"BigEye.h"
#include"Megaman.h"

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
		switch (id)
		{
		case SPR_GROUND:
			obj = new MGMObject();
			break;
		case SPR_OCTOPUSBATTERY:
			obj = new OctopusBattery();
			break;
		case SPR_PICKETMAN:
			obj = new PicketMan();
			break;
		case SPR_BIGEYE:
			obj = new BigEye();
			break;
		default:
			obj = new MGMObject();
			break;
		}

		allObjects[i] = obj;

		obj->init(x, y, width, height); //Khoi tao doi tuong

		if (id >= 0)
		{
			obj->sprite = MGMSpriteManager::getInstance()->sprites[id]; //Lấy sprite từ SpriteManager
			MGMMovableObject* mov = (MGMMovableObject*)obj;
			fs >> mov->spaceMove.x >> mov->spaceMove.y >> mov->spaceMove.width >> mov->spaceMove.height;
			mov->spaceMove.y = nRow * 16 - mov->spaceMove.y; // Chuyển tọa độ y hướng lên (tọa độ trong map)

		}
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
	}

	MGMStage::curStage = stages[0];

}

void MGMMap::updateStage()
{
	for (int i = 0; i < nStage; i++)
	{
		//if (MGMStage::curStage->index == i) continue;
		if (Collision::AABBCheck(Megaman::getInstance(), stages[i]))
		{
			MGMStage::curStage = stages[i];

			if (MGMCamera::getInstance()->y > MGMStage::curStage->getTop())
			{
				MGMCamera::getInstance()->dy = -1;
			}
			if (MGMCamera::getInstance()->getBottom() < MGMStage::curStage->getBottom())
			{
				//if (MGMCamera::getInstance()->y < MGMStage::curStage->getBottom() + MGMCamera::getInstance()->height)
				MGMCamera::getInstance()->dy = 1;
			}
			isUpdate = false;
		}
		//else isUpdate = true;
	}
	if (MGMStage::curStage->getBottom() <= MGMCamera::getInstance()->getBottom() &&MGMCamera::getInstance()->y <= MGMStage::curStage->getTop())
	{
		MGMCamera::getInstance()->dy = 0;
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

	int nGround = groundObjects.size();

	for (int iGround = 0; iGround < nGround; iGround++)
	{
		Collision::checkCollision(Megaman::getInstance(), groundObjects[iGround]);
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
}
