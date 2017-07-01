#include "QuadNode.h"
#include"MGMCamera.h"
#include"Collision.h"
#include "MGMMovableObject.h"

QuadNode::QuadNode(ifstream& fs, MGMObject** allObjects, int heightMap)
{
	fs >> id;
	fs >> x >> y >> width >> height;

	y = heightMap - y;


	int nNodes;
	fs >> nNodes;
	fs >> nObjects;
	if (nNodes != 0)
	{
		TL = new QuadNode(fs, allObjects, heightMap);
		TR = new QuadNode(fs, allObjects, heightMap);
		BL = new QuadNode(fs, allObjects, heightMap);
		BR = new QuadNode(fs, allObjects, heightMap);
		return;
	}

	if (nObjects != 0)
	{
		int index = 0;
		objects = new MGMObject*[nObjects];
		for (int i = 0; i < nObjects; i++)
		{
			fs >> index;
			objects[i] = allObjects[index];
		}
	}
}

void QuadNode::fillObjectToCamera()
{
	if (!Collision::AABBCheck(this, MGMCamera::getInstance()))
	{
		return;
	}
	if (nObjects != 0)
	{
		for (int i = 0; i < nObjects; i++)
		{ 
			MGMMovableObject* m = (MGMMovableObject*)objects[i]; // Nếu là Room thì không đưa vào Camera
			//if (m->id == 24)
			//	continue;
			//Dung add: xét với spaceMove để GreenBar xuất hiện
			if(m->id == 28 && Collision::AABBCheck(&m->spaceMove, MGMCamera::getInstance()))
				MGMCamera::getInstance()->objects.addObject(objects[i]);
			// ------------- Hết đoạn Dung add-----------------
			else
			if (Collision::AABBCheck(objects[i], MGMCamera::getInstance()))
			{
				if (!objects[i]->isKill)
					MGMCamera::getInstance()->objects.addObject(objects[i]);
				else MGMCamera::getInstance()->objects.isKilledObject._Add(objects[i]);
				if (objects[i]->collisionCategory == CC_ITEM){
					return;
				}
			}
			else MGMCamera::getInstance()->objects.isKilledObject._Add(objects[i]);

		}
		return;
	}

	if (TL != 0)
	{
		TL->fillObjectToCamera();
		TR->fillObjectToCamera();
		BL->fillObjectToCamera();
		BR->fillObjectToCamera();
	}

}


QuadNode::~QuadNode()
{
}
