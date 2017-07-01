#include "QuadTree.h"
#include<string>
#include "MGMSpriteManager.h"
#include"MGMMovableObject.h"
extern void LineDown(ifstream& fs, int lineCount);

QuadTree::QuadTree(char * quadtreepath, MGMObject** allObjects, int heightMap)
{
	ifstream fs(quadtreepath);
	 LineDown(fs, 1);
	BaseNode = new QuadNode(fs, allObjects, heightMap);
}
void QuadTree::restoreObjects(List<MGMObject*>* listObject){
	bool isRestore;
	for (int i = 0; i < listObject->size(); i++)
	{
		auto obj = listObject->at(i);
		isRestore = false;
		if (obj->id > 0)
		{
			MGMMovableObject* mov = (MGMMovableObject*)obj;
			if (!Collision::AABBCheck(MGMCamera::getInstance(), &mov->oldRect) && (!Collision::AABBCheck(MGMCamera::getInstance(), mov)) && (mov->id != 28)) // Dung: thêm điều kiện id != 28 để GreenBar không bị restore
			{
				obj->restoreObject();
				isRestore = true;

			}
			if (mov->id == SPR_FLYING_SHELL) {
				if (!Collision::AABBCheck(MGMCamera::getInstance(), mov)) {
					obj->restoreObject();
					isRestore = true;
				}
			}
		}
		if (isRestore) listObject->_Remove(obj);
	}
}
void QuadTree::RestoreClearObjectInCamera()
{
	List<MGMObject*>* allObjectInCams = &MGMCamera::getInstance()->objects.allObjects;
	List<MGMObject*>* KilledObjects = &MGMCamera::getInstance()->objects.isKilledObject;
	restoreObjects(KilledObjects);
	restoreObjects(allObjectInCams);
	MGMCamera::getInstance()->objects.clear();
}


void QuadTree::update()
{
	RestoreClearObjectInCamera();
	BaseNode->fillObjectToCamera();
}

QuadTree::~QuadTree()
{
}
