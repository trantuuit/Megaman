#pragma once
#include"QuadNode.h"
#include"MGMCamera.h"
#include"Collision.h"
class QuadTree
{
public:
	QuadNode* BaseNode;
	QuadTree(char* quadtreepath,MGMObject** allObjects,int heightMap);
	void restoreObjects(List<MGMObject*>* listObject);
	void RestoreClearObjectInCamera();

	void update();

	~QuadTree();
};

