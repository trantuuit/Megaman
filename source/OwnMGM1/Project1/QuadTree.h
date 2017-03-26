#pragma once
#include"QuadNode.h"
#include"MGMCamera.h"
#include"Collision.h"
class QuadTree
{
public:
	QuadNode* root;
	QuadTree(char* quadtreepath,MGMObject** allObjects,int heightMap);

	//xoa nhung doi tuong khong nam trong camera
	void removeObjectFromCamera();

	//do doi tuong tu node
	void fillObjectFromQNodeToCamera();

	void update();

	~QuadTree();
};

