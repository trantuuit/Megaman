#include "QuadTree.h"
#include<string>
#include "MGMSpriteManager.h"
#include"MGMMovableObject.h"
extern void ignoreLineIfstream(ifstream& fs, int lineCount);

QuadTree::QuadTree(char * quadtreepath, MGMObject** allObjects,int heightMap)
{
	ifstream fs(quadtreepath);
	ignoreLineIfstream(fs, 1);
	root = new QuadNode(fs, allObjects, heightMap);
}

void QuadTree::removeObjectFromCamera()
{
	List<MGMObject*>* allObjectInCams = &MGMCamera::getInstance()->objects.allObjects;
	int nObject = allObjectInCams->size();
	//cach cu khong can vung di chuyen
	//for (int i = 0; i < nObject; i++)
	//{
	//	auto obj = allObjectInCams->at(i);
	//	if (!Collision::AABBCheck(MGMCamera::getInstance(), obj) &&
	//		!Collision::AABBCheck(MGMCamera::getInstance(), &obj->oldRect))
	//	{
	//		obj->restoreObject();
	//		MGMCamera::getInstance()->objects.removeObject(obj);
	//		nObject--;
	//		i--;
	//	}
	//}

	for (int i = 0; i < nObject; i++)
	{
		auto obj = allObjectInCams->at(i);
		if (obj->sprite >= 0)
		{
			MGMMovableObject* mov = (MGMMovableObject*)obj;
			if (/*!Collision::AABBCheck(MGMCamera::getInstance(), &mov->spaceMove) &&*/ (!Collision::AABBCheck(MGMCamera::getInstance(),mov)))
			{
				obj->restoreObject();
			}
			if (mov->id == SPR_FLYING_SHELL){
				if (!Collision::AABBCheck(MGMCamera::getInstance(), mov)){
					obj->restoreObject();
				}
			}
		}
	}
	MGMCamera::getInstance()->objects.clear();
}

void QuadTree::fillObjectFromQNodeToCamera()
{
	root->fillObjectToCamera();
}

void QuadTree::update()
{
	//lay nhung doi tuong khong con nam trong camera nua ra
	removeObjectFromCamera();
	//do doi tuong vao camera
	fillObjectFromQNodeToCamera();
}

QuadTree::~QuadTree()
{
}
