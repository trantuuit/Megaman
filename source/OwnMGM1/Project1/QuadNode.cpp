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
		//loai 1- Co 4 node con 
		TL = new QuadNode(fs, allObjects, heightMap);
		TR = new QuadNode(fs, allObjects, heightMap);
		BL = new QuadNode(fs, allObjects, heightMap);
		BR = new QuadNode(fs, allObjects, heightMap);
		return;
	}

	if (nObjects != 0)
	{
		//loai 2 Node la
		int index = 0;
		objects = new MGMObject*[nObjects];
		for (int i = 0; i < nObjects; i++)
		{
			fs >> index;
			objects[i] = allObjects[index];
		}
	}
	//loai 3 
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
			if (Collision::AABBCheck(objects[i], MGMCamera::getInstance()))
			{
				if (!objects[i]->isKill)
					MGMCamera::getInstance()->objects.addObject(objects[i]);
				else MGMCamera::getInstance()->objects.isKilledObject._Add(objects[i]);
				if (objects[i]->collisionCategory == CC_ITEM){
					return;
				}
			}
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
